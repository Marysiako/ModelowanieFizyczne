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
        ofDrawSphere(position, 1.0);
    }
};

// Klasa EmitterSnow - Generuje cząstki z zakresu
class EmitterSnow {
public:
    ofVec3f position;                       // Początkowa pozycja emitera (środek zakresu)
    ofVec3f emissionRange;                  // Zakres emisji (rozciągłość w osiach x, y, z)
    ofVec3f velocityRange;                  // Zakres prędkości cząstek w osiach x, y, z
    ofColor color;                          // Kolor cząstek generowanych przez emiter
    float lifetime;                         // Czas życia każdej cząstki w sekundach
    float emissionRate;                     // Liczba cząstek generowanych na sekundę
    float timeSinceLastEmit;                // Czas, jaki upłynął od ostatniego wygenerowania cząstki
    float mass;                             // Masa cząsteczek

    // Konstruktor (pozycja, zakres emisji, zakres prędkości, kolor, czas życia, szybkość emisji, masa)
    EmitterSnow(ofVec3f pos, ofVec3f emitRange, ofVec3f velRange, ofColor col, float life, float rate, float m)
        : position(pos), emissionRange(emitRange), velocityRange(velRange), color(col), lifetime(life),
          emissionRate(rate), timeSinceLastEmit(0), mass(m) {}

    // Funkcja emitująca zwracająca wektor cząsteczek
    std::vector<Particle> emit(float dt) {
        std::vector<Particle> particles;                            // Wektor do przechowywania wygenerowanych cząstek
        timeSinceLastEmit += dt;                                    // Dodaje czas, jaki upłynął od ostatniej emisji
        int numToEmit = timeSinceLastEmit * emissionRate;           // Oblicza liczbę cząstek do wygenerowania
        timeSinceLastEmit -= numToEmit / emissionRate;              // Aktualizuje czas pozostały po emisji

        for (int i = 0; i < numToEmit; ++i) {
            ofVec3f randomPosition = ofVec3f(                      // Generuje losową pozycję w zakresie emisji
                ofRandom(position.x - emissionRange.x, position.x + emissionRange.x),
                ofRandom(position.y - emissionRange.y, position.y + emissionRange.y),
                ofRandom(position.z - emissionRange.z, position.z + emissionRange.z)
            );

            ofVec3f randomVelocity = ofVec3f(                      // Generuje losową prędkość dla każdej cząstki
                ofRandom(-velocityRange.x, velocityRange.x),
                ofRandom(-velocityRange.y, velocityRange.y),
                ofRandom(-velocityRange.z, velocityRange.z)
            );

            particles.push_back(Particle(randomPosition, randomVelocity, color, lifetime, mass));
        }
        return particles;
    }
};

// Klasa ParticleSystem - Reprezentuje cały system cząsteczek
class ParticleSystem {
public:
    std::vector<Particle> particles;        // Wektor przechowujący wszystkie cząsteczki
    EmitterSnow emitter;                    // Emiter generujący nowe cząsteczki

    // Konstruktor uwzględniający emiter
    ParticleSystem(const EmitterSnow& em)
        : emitter(em) {}

    void applyForce(const ofVec3f& force) { // Funkcja dodająca siłę do cząsteczek
        for (auto& p : particles) {
            p.applyForce(force);
        }
    }

    void update(float dt) {
        auto newParticles = emitter.emit(dt);               // Wywołuje metodę emit emitera
        particles.insert(particles.end(), newParticles.begin(), newParticles.end());    // Dodaje nowo wygenerowane cząstki

        for (auto& p : particles) {
            p.update(dt);           // Aktualizacja pozycji cząsteczek
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
        for (const auto& p : particles) { // Rysowanie cząsteczek
            p.draw();
        }
    }
};
class ofApp : public ofBaseApp{

	public:

		ParticleSystem* particleSystem;
    	ofEasyCam cam;
		ofImage backgroundImage;

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

