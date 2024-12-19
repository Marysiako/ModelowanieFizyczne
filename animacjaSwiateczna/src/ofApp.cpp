#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest(); // Włącza test głębi   - żeby cząstecki za kulą sie chowały a przed były widoczne
//                          pozycja    , zakres emisji,         predkosc               kolor             czas zycia    ilosc na sek, masa
    EmitterSnow emitter(ofVec3f(0, 500, 0),    // Pozycja
                    ofVec3f(1000, 0, 1000),  // Zakres emisji
                    ofVec3f(1, 1, 1),    // Zakres prędkości
                    ofColor(255, 255, 255), // Kolor
                    5.0f,                 // Czas życia
                    400,                  // Szybkość emisji
                    1.0f);                // Masa cząstki
    particleSystem = new ParticleSystem(emitter);

    backgroundImage.load("background.jpg"); // Załaduj obrazek
}

//--------------------------------------------------------------
void ofApp::update(){                            //Aktualizuje logikę aplikacji
    float dt = ofGetLastFrameTime();            //Oblicza czas między klatkami (dt w sekundach)
    ofVec3f wind(1, -2, 0);                      //Wprowadza siłę wiatru (5 jednostek w prawo)
    particleSystem->applyForce(wind);           //Dodaje siłę do każdej cząstki
    particleSystem->update(dt);                 //Aktualizuje położenie i stan cząstek
}

//--------------------------------------------------------------
void ofApp::draw(){                             //Rysuje scenę
    ofSetColor(255, 255, 255, 255);
    ofDisableDepthTest();
    backgroundImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    cam.begin();                               //Aktywuje kamerę 3D
    ofEnableDepthTest();  
    //ofDrawAxis(200);                            //Ośie układu współrzędnych
    particleSystem->draw();                     //Rysuje wszystkie cząstki

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){                //Obsługuje naciśnięcia klawiszy
    /*if (key == 'r') {                           //Klawisz 'r' resetuje system cząsteczek
        delete particleSystem;                  //Usuwa istniejący system 
        EmitterSnow emitter(ofVec3f(0, 0, 0),    // Pozycja
                    ofVec3f(1000, 0, 0),  // Zakres emisji
                    ofVec3f(10, 5, 5),    // Zakres prędkości
                    ofColor(255, 255, 255), // Kolor
                    7.0f,                 // Czas życia
                    100,                  // Szybkość emisji
                    1.0f);                // Masa cząstki
        particleSystem = new ParticleSystem(emitter);
    }
    */
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
