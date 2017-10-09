#include "ofMain.h"
#include "ofApp.h"

#define FULLSCREEN

//========================================================================
int main( )
{
	/*--
		Inmensa maravilla,
		Implacable como unico,
		frio y aterrador,
		Pero es...
		nuestro hogar.
	*/
	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);

#ifdef FULLSCREEN
	settings.windowMode = ofWindowMode::OF_FULLSCREEN;
#else
	settings.windowMode = ofWindowMode::OF_WINDOW;
#endif // FULLSCREEN

	ofCreateWindow(settings);	// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}