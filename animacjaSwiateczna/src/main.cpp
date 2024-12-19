#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //Okno w trybie okienkowym - może być zmienione na OF_FULLSCREEN

	auto window = ofCreateWindow(settings);		//Tworzy okno z podanymi ustawieniami

	ofRunApp(window, make_shared<ofApp>());	//Uruchamia instancję klasy `ofApp`
	ofRunMainLoop();						//Główna pętla aplikacji

}
