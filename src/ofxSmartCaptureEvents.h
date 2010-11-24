/*
 *  ofxSmartCaptureEvent.h
 *  ofxSmartCapture
 *
 *  Created by Paulo on 10/5/10.
 *  Copyleft 2010. Please help improve this code.
 */

#ifndef _OFX_SMART_CAPTURE_EVENTS
#define _OFX_SMART_CAPTURE_EVENTS


#include "ofMain.h"
class ofxSmartCaptureEventArgs {
public:
	ofPoint								captureSize;
};

class ofxSmartCaptureEvents{
	
public:
	ofEvent<ofxSmartCaptureEventArgs>	connectionEvt;
	ofxSmartCaptureEventArgs			connectionEvtArgs;
};
#endif