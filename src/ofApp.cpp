#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
//	ofColor::setHsb;
	ofSetFrameRate(60);

#ifdef TARGET_OPENGLES
	shader.load("shadersES2/shader");
#else
	if (ofIsGLProgrammableRenderer())
	{
		shader.load("shadersGL3/shader");
	}
	else
	{
		shader.load("shadersGL2/shader");
	}
#endif

	float planeScale = 0.75;
	int planeWidth = ofGetWidth() * planeScale;
	int planeHeight = ofGetHeight() * planeScale;
	int ds = 20; // grid size
	int nCols = planeWidth / ds; // num of columns
	int nRows = planeHeight / ds; // num of rows

	plane.set(planeWidth, planeHeight, nCols, nRows, ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES);

	// arduino connection
	arduino.connect("COM14", 57600);
	arduino.sendFirmwareVersionRequest(); // <- this is mandatory!!!

	//if (arduino.isInitialized()) printf("Connected");

	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino = false;

	// osc sender
	sender.setup(HOST, PORT);

}

//--------------------------------------------------------------
void ofApp::update()
{
	updateArduino();

	ofxOscMessage m_soundVelocity;
	m_soundVelocity.setAddress("/ID1/velocity");

#ifdef IS_FLASHLIGHT
	m_soundVelocity.addFloatArg(ofMap(photoValue, 0, 1023, 0.35, 2));
#else
	m_soundVelocity.addFloatArg(ofMap(photoValue, 0, AMBIENT_MAX_RESISTENCE, 0.8, 2));
#endif // IS_FLASHLIGHT
	sender.sendMessage(m_soundVelocity, false);
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int &version)
{
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
	printf("Arduino connected");

	bSetupArduino = true;

	// set pin A1 to analog input
	arduino.sendAnalogPinReporting(1, ARD_ANALOG);

	// Listen for changes on the digital and analog pins
	//ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino()
{
	arduino.update();

	if (!bSetupArduino) return;

}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int &pinNum)
{
	// do nothing
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int &pinNum)
{
	//printf("Hello");
	photoString = "analog pin: " + ofToString(pinNum) + " = " + ofToString(arduino.getAnalog(pinNum));
	ofLogNotice() << photoString;
	photoValue = arduino.getAnalog(pinNum);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(255);

	shader.begin();

	shader.setUniform2f("iResolution", ofVec2f(1024, 768));
	shader.setUniform1f("iTime", ofGetElapsedTimef());
	shader.setUniform2f("iMouse", ofVec2f(ofGetMouseX(), ofGetMouseY()));
	// iTemperature 1 for harm 0 for cold
#ifdef IS_FLASHLIGHT
	shader.setUniform1f("iTemperature", ofMap(photoValue, 0, 1023, 0, 1));
#else
	shader.setUniform1f("iTemperature", ofMap(photoValue, 0, AMBIENT_MAX_RESISTENCE, 0, 1));
#endif // IS_FLASHLIGHT


	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

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
