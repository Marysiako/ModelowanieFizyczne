#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){                    //Inicjalizacja aplikacji.
    ofSetFrameRate(60);                 //Ustawia odświeżanie ekranu na 60 FPS
    ofBackground(0);                    //Ustawia czarne tło
    // emiter    (          pozycja,      zakres predkosci,            kolor,           czas zycia-5sek,  ile czasteczek na sekunde,  masa)
    Emitter emitter(ofVec3f(0, -300, 0), ofVec3f(50, 50, 50), ofColor(2500, 0, 60),      3.0f,               1000,               1.0f);
    particleSystem = new ParticleSystem(emitter);       //tworzenie particle system
}

//--------------------------------------------------------------
void ofApp::update(){                            //Aktualizuje logikę aplikacji
    float dt = ofGetLastFrameTime();            //Oblicza czas między klatkami (dt w sekundach)
    ofVec3f wind(1, 2, 0);                      //Wprowadza siłę wiatru (5 jednostek w prawo)
    particleSystem->applyForce(wind);           //Dodaje siłę do każdej cząstki
    particleSystem->update(dt);                 //Aktualizuje położenie i stan cząstek
}

//--------------------------------------------------------------
void ofApp::draw(){                             //Rysuje scenę
    cam.begin();                                //Aktywuje kamerę 3D
    particleSystem->draw();                     //Rysuje wszystkie cząstki
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){                //Obsługuje naciśnięcia klawiszy
    if (key == 'r') {                           //Klawisz 'r' resetuje system cząsteczek
        delete particleSystem;                  //Usuwa istniejący system 
        Emitter emitter(ofVec3f(0, -300, 0), ofVec3f(100, 100, 100), ofColor(255, 0, 0), 5.0f, 50, 1.0f);
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
