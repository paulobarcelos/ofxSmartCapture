#include "testApp.h"

///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::setup(){
	videoInverted = NULL;
	
	// add this listener to know when there be a sucessfull camera conection
	// remeber to add it BEFORE starting the capture, otherwise you may lose the first connection event.
	ofAddListener(capture.events.connectionEvt, this, &testApp::onCameraConnection);
	
	capture.startCapture(320,	// "desired" capture width
						 240,	// "desired" cpature height
						 true,	// use GL Texture
						 2,		// interval (in seconds) to try to reconect in case the camera is not available.
						 2		// maximum interval (in seconds) between 2 new frames before we consider the camera is frozen.
						 );
	
}
///////////////////////////////////////////////////////////////////////////////////
// onConnection -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::onCameraConnection(ofxSmartCaptureEventArgs &args){
	camWidth = args.captureSize.x;	// the REAL capture size, in case the one we requested was not supported bu the camera.
	camHeight = args.captureSize.y;
	
	if(videoInverted != NULL) delete videoInverted;
	videoInverted = new unsigned char[camWidth*camHeight*3]; // Allocate memory to the proper size.
	videoTexture.clear();
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	
}
///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::update(){
	capture.update();
	
	if (capture.isCameraAvailable()){ // Don't do anything stupid if the camera is not available.
		
		if (capture.isFrameNew()){		
			int totalPixels = camWidth*camHeight*3;
			unsigned char * pixels = capture.getPixels();
			for (int i = 0; i < totalPixels; i++){
				videoInverted[i] = 255 - pixels[i];
			}
			videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
		}
	}	
}
///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::draw(){
	if (capture.isCameraAvailable()){ // Don't do anything stupid if the camera is not available.
		ofSetColor(0xffffff);
		capture.draw(20,20);
		videoTexture.draw(20+camWidth,20,camWidth,camHeight);
	}
}
///////////////////////////////////////////////////////////////////////////////////
// keyPressed ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::keyPressed(int key){

	if (key=='s')
		capture.videoSettings();

}
