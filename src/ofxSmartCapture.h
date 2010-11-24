/*
 *  ofxSmartCapture.h
 *  ofxSmartCapture
 *
 *  Created by Paulo Barcelos on 10/5/10.
 *  Copyleft 2010. Please help improve this code.
 *
 *
 *	This codes extends OF's videoGrabber adding and auto reconection feature 
 *	in case no camera is detected or if the camera suddenly stops suplying frames.
 *
 *	Everytime the reconnection is sucessfull, it dispatches an event with the capture size
 *	in case you need to reallocate memory based on the real dimensions of teh pixel frame;
 *
 */

#ifndef _OFX_SMART_CAPTURE
#define _OFX_SMART_CAPTURE

#include "ofMain.h"
#include "ofxSmartCaptureVideoGrabber.h"
#include "ofxSmartCaptureEvents.h"

#define MAX_SMART_CAPTURE_OBJECTS	10

////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class ofxSmartCapture : public ofxSmartCaptureVideoGrabber{
	
public:
							
	ofxSmartCapture();
	
	void					startCapture(int width,							// "desired" capture width
										 int height,						// "desired" cpature height
										 bool useTexture = true,			// use GL Texture
										 float reconnectionTimeout = 5,		// interval to try to reconect in case the camera is not available.
										 float frameGrabTolerance = 5		// maximum interval between 2 new frames before we consider the camera is frozen.
										 );
	
	void					draw(float x, float y, float w = -1, float h = -1);
	void					drawInfo(float x, float y, float w, float h); // TODO: draw status of the camera, ex. message when the camera is not working

	void					update();					// call this in your app's update(). It will automatically call grabFrame() if the camera is available.
	ofPoint					getCaptureSize();			// returns the real dimensions of the capture. Migth be different from the ones requested.
	bool					isCameraAvailable();		// tells if the capture is up and running;
	
	ofxSmartCaptureEvents	events;
	
	static int				getNumInstances(){ return numInstances;}
	static ofxSmartCapture*	getInstanceAt(int ID){ return sharedInstance_[ID]; }
	
	
	
private:	
	
	static int						numInstances;
	static ofxSmartCapture*			sharedInstance_[MAX_SMART_CAPTURE_OBJECTS]; 

	int								missedCameraAvalibleFrames;
	int								missedCaptureFrames;	
	ofPoint							lastRequestedCaptureSize;
	
	float							reconnectionTimeout;
	float							frameGrabTolerance;
	
	float							lastFrameTimestamp;
	float							lastConnectionFailureTimestamp;
	
	bool							useTexture;
	
};
#endif