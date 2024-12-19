#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest(); // Włącza test głębi   - żeby cząstecki za kulą sie chowały a przed były widoczne
//                          pozycja             predkosc               kolor                ilosc na sek, masa
    Emitter emitter(ofVec3f(-300, -250, 0), ofVec3f(100, 100, 100), ofColor(200, 0, 40), 3.0f, 1000, 1.0f);
    particleSystem = new ParticleSystem(emitter);

    // Pozycja i promień kuli do kolizji
    particleSystem->spherePosition = ofVec3f(0, 0, 0);
    particleSystem->sphereRadius = 100.0f;
}

//--------------------------------------------------------------
void ofApp::update(){                            //Aktualizuje logikę aplikacji
    float dt = ofGetLastFrameTime();            //Oblicza czas między klatkami (dt w sekundach)
    ofVec3f wind(2, 2, 0);                      //Wprowadza siłę wiatru (5 jednostek w prawo)
    particleSystem->applyForce(wind);           //Dodaje siłę do każdej cząstki
    particleSystem->update(dt);                 //Aktualizuje położenie i stan cząstek
}

//--------------------------------------------------------------
void ofApp::draw(){                             //Rysuje scenę
    cam.begin();                                //Aktywuje kamerę 3D
    ofDrawAxis(200);                            //Ośie układu współrzędnych
    particleSystem->draw();                     //Rysuje wszystkie cząstki
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){                //Obsługuje naciśnięcia klawiszy
    if (key == 'r') {                           //Klawisz 'r' resetuje system cząsteczek
        delete particleSystem;                  //Usuwa istniejący system 
        Emitter emitter(ofVec3f(-300, -250, 0), ofVec3f(100, 100, 100), ofColor(200, 0, 40), 3.0f, 1000, 1.0f);
        particleSystem = new ParticleSystem(emitter);
    }
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
