/*
 *  ofxSmartCapture.cpp
 *  ofxSmartCapture
 *
 *  Created by Paulo on 10/5/10.
 *  Copyleft 2010. Please help improve this code.
 */

#include "ofxSmartCapture.h"

ofxSmartCapture* ofxSmartCapture::sharedInstance_[] = {NULL};	//init all to NULL
int ofxSmartCapture::numInstances = 0;

ofxSmartCapture::ofxSmartCapture(){
	if ( sharedInstance_[numInstances] == NULL ){
		sharedInstance_[numInstances] = this;
		numInstances ++;
		//printf("ofxSmartCapture construct %d\n", numInstances);
	}	
}

///////////////////////////////////////////////////////////////////////////////////
// startCapture -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ofxSmartCapture::startCapture(int width, int height, bool useTexture, float reconnectionTimeout, float frameGrabTolerance)
{	
	this->useTexture = useTexture;
	this->reconnectionTimeout = reconnectionTimeout;
	this->frameGrabTolerance = frameGrabTolerance;
	
	lastRequestedCaptureSize = ofPoint (width,height,0);
	
    listDevices();
	
    if (isCameraAvailable())
    {
        close();
        initGrabber(lastRequestedCaptureSize.x, lastRequestedCaptureSize.y, useTexture);
		lastFrameTimestamp = ofGetElapsedTimef();
		// dispatch event
		events.connectionEvtArgs.captureSize.x = this->width;
		events.connectionEvtArgs.captureSize.y = this->height;	
		ofNotifyEvent(events.connectionEvt, events.connectionEvtArgs);
	}
	else{
		ofLog(OF_LOG_ERROR, "ofxSmartCapture: Cant startCapture, no camera is available");
		lastConnectionFailureTimestamp = ofGetElapsedTimef();
	}
}


///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ofxSmartCapture::update(){
	if (isCameraAvailable())
	{
		grabFrame();
		
		if (isFrameNew()) {

			lastFrameTimestamp = ofGetElapsedTimef();
		
		} else {

			if((ofGetElapsedTimef() - lastFrameTimestamp) >= frameGrabTolerance) 
				startCapture(lastRequestedCaptureSize.x, lastRequestedCaptureSize.y, useTexture, reconnectionTimeout, frameGrabTolerance);

		}
	}
	else
	{
		if((ofGetElapsedTimef() - lastConnectionFailureTimestamp) >= reconnectionTimeout) 
			startCapture(lastRequestedCaptureSize.x, lastRequestedCaptureSize.y, useTexture, reconnectionTimeout, frameGrabTolerance);
	}
	
}
///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ofxSmartCapture::draw(float x, float y, float w, float h){
	if(isCameraAvailable()) {
		float newW = (w == -1) ? getCaptureSize().x : w;
		float newH = (h == -1) ? getCaptureSize().y : h;
		ofxSmartCaptureVideoGrabber::draw(x, y, newW, newH);
	}
	else{
		cout <<  "camera not available" << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////
// drawInfo -----------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ofxSmartCapture::drawInfo(float x, float y, float w, float h){
	// TODO: draw status of the camera, ex. message when the camera is not working
}
///////////////////////////////////////////////////////////////////////////////////
// isCameraAvailable -------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool ofxSmartCapture::isCameraAvailable(){
	return (videoInputDevices > 0) ? true : false ;
}
///////////////////////////////////////////////////////////////////////////////////
// getCaptureSize -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ofPoint ofxSmartCapture::getCaptureSize(){
	return ofPoint(width, height, 0);
}