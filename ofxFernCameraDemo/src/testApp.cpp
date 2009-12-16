#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	int camW = 640;
	int camH = 480;

	fern.initTracker("model.bmp",camW, camH);
	grabber.initGrabber(camW, camH);
	colorImg.allocate(camW, camH);
	img.allocate(camW, camH);
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	grabber.update();	
	if( grabber.isFrameNew() ){
		colorImg = grabber.getPixels();
		img = colorImg;
		fern.update(img);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xFFFFFF);
	fern.draw(0, 0, 640, 480);

	ofDrawBitmapString("keys 1-5 do stuff\nfps: "+ofToString(ofGetFrameRate(), 2), 10, 500);
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	fern.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

