#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxFern.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		ofVideoGrabber grabber;

		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage img;
		ofxFern fern;
		
		bool showTracker;
};
