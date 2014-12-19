/*
 *  ofxFern.h
 *  
 *
 *  Created by theo on 16/12/2009.
 *  Copyright 2009. All rights reserved.
 *
 *	Updated by Dan Wilcox <danomatika@gmail.com> 2012
 */

#pragma once 

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "mcv.h"
#include "planar_pattern_detector_builder.h"
#include "template_matching_based_tracker.h"

struct ofxFernTrackedMarker{

	ofxFernTrackedMarker() {
		tracked = false;
	}

	void draw() {
		ofBeginShape();
			ofVertex(points[0]);
			ofVertex(points[1]);
			ofVertex(points[2]);
			ofVertex(points[3]);
		ofEndShape(true);
	}

	ofPoint points[4];	//< quad points
	bool tracked;
};

class ofxFern{

	public:
		
		ofxFern();
		~ofxFern();

		/// set the marker image file and incoming image size
		void setup(string marker, int width, int height);
		
		/// search for marker in an incoming image
		/// dimensions should match size in setup()
		void update(ofxCvGrayscaleImage & grayImg);
		
		/// reset the tracker, restarts detected next frame
		void resetTracker();
		
		/// the tracked marker
		ofxFernTrackedMarker trackedMarker;
		
		/// draw the tracker image
		void draw(float x, float y, float w, float h);
		
		/// show tracked locations in the tracker image?
		void showLocations(bool show)	{show_tracked_locations = show;}
		bool getShowLocations()			{return show_tracked_locations;}
		
		/// show keypoints in the tracker image?
		void showKeypoints(bool show)	{show_keypoints = show;}
		bool getShowKeypoints()			{return show_keypoints;}
		
	protected:
				
		void draw_quadrangle(IplImage * frame, int u0, int v0, int u1, int v1, int u2, int v2, int u3, int v3, CvScalar color, int thickness = 1);
		void draw_detected_position(IplImage * frame, planar_pattern_detector * detector);
		void draw_initial_rectangle(IplImage * frame, template_matching_based_tracker * tracker);
		void draw_tracked_position(IplImage * frame, template_matching_based_tracker * tracker);
		void draw_tracked_locations(IplImage * frame, template_matching_based_tracker * tracker);
		void draw_detected_keypoints(IplImage * frame, planar_pattern_detector * detector);
		void draw_recognized_keypoints(IplImage * frame, planar_pattern_detector * detector);
		
		void detect(IplImage * frame);
		
		void setTrackedMarker(template_matching_based_tracker * tracker);
		void setTrackedMarker(planar_pattern_detector * detector);

		bool bSetup;		
		ofxCvGrayscaleImage img;

		bool show_tracked_locations;
		bool show_keypoints;
		planar_pattern_detector * detector;
		template_matching_based_tracker * tracker;
		bool bDetected;	///< has the marker been detected?
};
