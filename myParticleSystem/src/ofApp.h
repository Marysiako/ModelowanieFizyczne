#pragma once

#include "ofMain.h"

// Klasa Particle       -       Definiuje pojedynczą cząstkę
class Particle {
public:
    ofVec3f position;                       //Początkowa pozycja cząstki.
    ofVec3f velocity;                       //Początkowa prędkość
    ofColor color;                          //Początkowy kolor
    float lifetime;                         //Czas życia w sekundach
    float age;                              //Wiek
    float mass;                             //Masa początkowa

    Particle(ofVec3f pos, ofVec3f vel, ofColor col, float life, float m)
        : position(pos), velocity(vel), color(col), lifetime(life), age(0), mass(m) {}

    void applyForce(const ofVec3f& force) {     //Dodaje siłę do cząstki, zmieniając jej prędkość (velocity)
        velocity += force / mass;
    }

    void update(float dt) {                    //Aktualizuje stan cząstki
        position += velocity * dt;             //Zmienia pozycję (`position`) w zależności od prędkości i czasu
        age += dt;                             //Zwiększa wiek (`age`)
    }

    bool isDead() const {                   //Sprawdza, czy cząstka przekroczyła czas życia
        return age > lifetime;
    }

    void draw() const {                     //Rysuje cząstkę jako kulę o promieniu 3
        ofSetColor(color);
        ofDrawSphere(position, 3.0);
    }
};

// Klasa Emitter    -   Generuje cząstki
class Emitter {
public:
    ofVec3f position;                       // Pozycja emitera w przestrzeni 3D (x, y, z)
    ofVec3f velocityRange;                  //Zakres prędkości cząstek w osiach x, y, z - Pozwala generować losowe prędkości w określonych przedziałach
    ofColor color;                          //Kolor cząstek generowanych przez emiter
    float lifetime;                         //Czas życia każdej cząstki w sekundach
    float emissionRate;                     //Liczba cząstek generowanych na sekundę
    float timeSinceLastEmit;                // Czas, jaki upłynął od ostatniego wygenerowania cząstki 
    float mass;                             //Masa cząsteczek

    //Konstruktor (pozycja, zakres predkosci, kolor, czas życia, szybkość emisji, czas od oststniej emisji -najpier0, masa)
    Emitter(ofVec3f pos, ofVec3f velRange, ofColor col, float life, float rate, float m)
        : position(pos), velocityRange(velRange), color(col), lifetime(life),
          emissionRate(rate), timeSinceLastEmit(0), mass(m) {}

    //Funkcja emitująca zwracająca wektor cząsteczek
    std::vector<Particle> emit(float dt) {
        std::vector<Particle> particles;                            //Wektor do przechowywania wygenerowanych cząstek.
        timeSinceLastEmit += dt;                                    //Dodaje czas, jaki upłynął od ostatniej emisji, aby obliczyć, czy należy wygenerować nowe cząstki
        int numToEmit = timeSinceLastEmit * emissionRate;           //Oblicza liczbę cząstek, które powinny zostać wygenerowane //np 0.1 sek z 100/sek -> numToEmit = 0.1 * 100 = 10
        timeSinceLastEmit -= numToEmit / emissionRate;              // Aktualizuje czas, który pozostał po emisji tych cząstek

        for (int i = 0; i < numToEmit; ++i) {                       //Pętla generuje tyle cząstek, ile wynosi numToEmit
            ofVec3f randomVelocity = ofVec3f(                       //Generuje losową prędkość dla każdej cząstki
                ofRandom(-velocityRange.x, velocityRange.x),
                ofRandom(-velocityRange.y, velocityRange.y),
                ofRandom(-velocityRange.z, velocityRange.z)
            );
            particles.push_back(Particle(position, randomVelocity, color, lifetime, mass));     //Tworzy nową cząstkę i dodaje ją do wektora particles
        }
        return particles;
    }
};

// Klasa ParticleSystem - Reprezentuje cały system cząsteczek
class ParticleSystem {
public:
    std::vector<Particle> particles;            //Vektor przechowujący wszystkie cząsteczki
    Emitter emitter;                            //Emiter generujący nowe cząsteczki

    ofVec3f spherePosition;                     // Położenie i promień kuli
    float sphereRadius;

    // Konstruktor uwzględniający emiter i kulę 
    ParticleSystem(const Emitter& em)
        : emitter(em), spherePosition(ofVec3f(0, 0, 0)), sphereRadius(100.0f) {}

    void applyForce(const ofVec3f& force) {     //Funkcja dodajaca siłe do cząsteczek
        for (auto& p : particles) {
            p.applyForce(force);
        }
    }

    void update(float dt) {
        auto newParticles = emitter.emit(dt);               //Wywołuje metodę emit emitera, aby wygenerować nowe cząstki 
        particles.insert(particles.end(), newParticles.begin(), newParticles.end());    //Dodaje nowo wygenerowane cząstki do istniejącego zbioru cząstek
        for (auto& p : particles) {
            p.update(dt);           //Aktualizacja pozycji cząsteczek
            handleCollision(p);     // Obsługa kolizji z kulą
        }
        for (auto it = particles.begin(); it != particles.end();) {
            if (it->isDead()) {
                it = particles.erase(it); // Usuwa cząstkę i aktualizuje iterator
            } else {
                    ++it; // Przechodzi do następnej cząstki
            }
        }
    }

    void draw() const {
        ofSetColor(100, 100, 255);
        ofDrawSphere(spherePosition, sphereRadius);         // Rysowanie kuli

        for (const auto& p : particles) {                   //Rysowanie cząsteczek
            p.draw();
        }


    }

private:
    void handleCollision(Particle& p) {
        ofVec3f toParticle = p.position - spherePosition;               //Oblicza wektor od środka kuli (spherePosition) do pozycji cząstki (p.position)

        if (toParticle.length() <= sphereRadius) {                      //Sprawdza, czy cząstka znajduje się wewnątrz lub na powierzchni kuli, mierząc długość wektora toParticle
            toParticle.normalize();                                     //Normalizacja wektora - zmienia jego długość na 1, ale zachowuje kierunek
                                                                                // Odbicie cząstki od powierzchni kuli
            p.velocity -= 2 * (p.velocity.dot(toParticle)) * toParticle;        //dot - Iloczyn skalarny

            // Przesunięcie cząstki na zewnątrz kuli
            //p.position = spherePosition + toParticle * sphereRadius;
        }
    }
};

class ofApp : public ofBaseApp{

	public:

		ParticleSystem* particleSystem;
    	ofEasyCam cam;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};

