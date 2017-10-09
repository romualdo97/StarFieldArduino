#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxOsc.h"

#define PORT 12345
#define HOST "localhost"

// do you have a flashlight?
//#define IS_FLASHLIGHT
#define AMBIENT_MAX_RESISTENCE 330 // if not use ambient illumination

class ofApp : public ofBaseApp{

	public:
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

		ofxOscSender sender;

		ofShader shader;
		ofPlanePrimitive plane;
		ofArduino arduino;
		bool bSetupArduino;

	private:
		void setupArduino(const int &version);
		void digitalPinChanged(const int &version);
		void analogPinChanged(const int &version);
		void updateArduino();

		// string buttonState;
		string photoString;
		int photoValue;

};