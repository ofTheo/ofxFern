/*
 *  ofxFern.h
 *  
 *
 *  Created by theo on 16/12/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 

#include "ofxOpenCv.h"

#include "mcv.h"
#include "planar_pattern_detector_builder.h"
#include "template_matching_based_tracker.h"

class ofxFern{
	public:
		
		ofxFern();
		~ofxFern();

		void initTracker(string marker, int width, int height);
		void update(ofxCvGrayscaleImage & grayImg );

		void draw(float x, float y, float w, float h);
		
		//just for now - will be removed
		void keyPressed(int key);
		
	protected:
				
		void draw_quadrangle(IplImage * frame, int u0, int v0, int u1, int v1, int u2, int v2, int u3, int v3, CvScalar color, int thickness = 1);
		void draw_detected_position(IplImage * frame, planar_pattern_detector * detector);
		void draw_initial_rectangle(IplImage * frame, template_matching_based_tracker * tracker);
		void draw_tracked_position(IplImage * frame, template_matching_based_tracker * tracker);
		void draw_tracked_locations(IplImage * frame, template_matching_based_tracker * tracker);
		void draw_detected_keypoints(IplImage * frame, planar_pattern_detector * detector);
		void draw_recognized_keypoints(IplImage * frame, planar_pattern_detector * detector);

		IplImage * detect(IplImage * frame);

		
		ofxCvGrayscaleImage img;

		int mode;
		bool show_tracked_locations;
		bool show_keypoints;
		planar_pattern_detector * detector;
		template_matching_based_tracker * tracker;

		
};