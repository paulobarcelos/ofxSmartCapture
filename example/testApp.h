#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxSmartCapture.h"

class testApp : public ofBaseApp{
	
public:
	void				setup();
	void				update();
	void				draw();
	void				onCameraConnection (ofxSmartCaptureEventArgs &args);
	void				keyPressed(int key);
	
	ofxSmartCapture		capture;
	unsigned char * 	videoInverted;
	ofTexture			videoTexture;
	int 				camWidth;
	int 				camHeight;
		
	
};
#endif
