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

    void draw() const {                     //Rysuje cząstkę jako kulę o promieniu 2
        ofSetColor(color);
        ofDrawSphere(position, 1.0);
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
    std::vector<Particle> particles;
    Emitter emitter;

    ParticleSystem(const Emitter& em) : emitter(em) {}

    void applyForce(const ofVec3f& force) {
        for (auto& p : particles) {
            p.applyForce(force);
        }
    }

    void update(float dt) {
        auto newParticles = emitter.emit(dt);
        particles.insert(particles.end(), newParticles.begin(), newParticles.end());
        for (auto& p : particles) {
            p.update(dt);
        }
        particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                           [](const Particle& p) { return p.isDead(); }),
            particles.end()
        );
    }

    void draw() const {
        for (const auto& p : particles) {
            p.draw();
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

