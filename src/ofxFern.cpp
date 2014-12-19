/*
 *  ofxFern.cpp
 *  
 *
 *  Created by theo on 16/12/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 *	Updated by Dan Wilcox <danomatika@gmail.com> 2012
 */

#include "ofxFern.h"

//------------------------------------------------------------------------
ofxFern::ofxFern(){
	bSetup = false;
	detector = NULL;
	tracker  = NULL;
	show_tracked_locations = true;
	show_keypoints = true;
	bDetected = false;
}

//------------------------------------------------------------------------
ofxFern::~ofxFern(){
	if(detector != NULL){
		delete detector;
		detector = NULL;
	}
	if(tracker != NULL){
		delete tracker;
		tracker = NULL;
	}
}

//------------------------------------------------------------------------
void ofxFern::setup(string marker, int width, int height){
	
	img.allocate(width, height); 
	marker = ofToDataPath(marker);

	string model_image			= marker;
	string sequence_format		= "";
	string video_file			= "";

	affine_transformation_range range;
	detector = planar_pattern_detector_builder::build_with_cache(model_image.c_str(),
					&range, 400, 5000, 0.0, 32, 7, 4,30, 12, 10000, 200);

  if(!detector) {
    ofLog(OF_LOG_ERROR, "ofxFern: Unable to build detector");
    return ;
  }

  detector->set_maximum_number_of_points_to_detect(1000);

  tracker = new template_matching_based_tracker();
  string trackerfn = model_image + string(".tracker_data");
  if(!tracker->load(trackerfn.c_str())) {
    ofLog(OF_LOG_NOTICE, "ofxFern: Training template matching...");
    tracker->learn(detector->model_image,
		   5, // number of used matrices (coarse-to-fine)
		   40, // max motion in pixel used to train to coarser matrix
		   20, 20, // defines a grid. Each cell will have one tracked point.
		   detector->u_corner[0], detector->v_corner[1],
		   detector->u_corner[2], detector->v_corner[2],
		   40, 40, // neighbordhood for local maxima selection
		   10000 // number of training samples
		   );
    tracker->save(trackerfn.c_str());
  }
  tracker->initialize();
  bSetup = true;
}

//------------------------------------------------------------------------
void ofxFern::resetTracker() {
	bDetected = false;
}

//------------------------------------------------------------------------
void ofxFern::update(ofxCvGrayscaleImage & grayImg ){
	if(!bSetup){
		ofLog(OF_LOG_ERROR, "ofxFern: cannot update, call setup() first");
		return;
	}
	img = grayImg;
	detect(img.getCvImage());
	img.flagImageChanged();
}

//------------------------------------------------------------------------
void ofxFern::draw(float x, float y, float w, float h){
    img.draw(x,y,w,h);
}

// PROTECTED

//------------------------------------------------------------------------
void ofxFern::draw_quadrangle(IplImage * frame, int u0, int v0, int u1, int v1, int u2, int v2, int u3, int v3, CvScalar color, int thickness){
	cvLine(frame, cvPoint(u0, v0), cvPoint(u1, v1), color, thickness);
	cvLine(frame, cvPoint(u1, v1), cvPoint(u2, v2), color, thickness);
	cvLine(frame, cvPoint(u2, v2), cvPoint(u3, v3), color, thickness);
	cvLine(frame, cvPoint(u3, v3), cvPoint(u0, v0), color, thickness);
	ofSetLineWidth(1);
}

//------------------------------------------------------------------------
void ofxFern::draw_detected_position(IplImage * frame, planar_pattern_detector * detector){
	draw_quadrangle(frame,
		  detector->detected_u_corner[0], detector->detected_v_corner[0],
		  detector->detected_u_corner[1], detector->detected_v_corner[1],
		  detector->detected_u_corner[2], detector->detected_v_corner[2],
		  detector->detected_u_corner[3], detector->detected_v_corner[3],
		  cvScalar(255), 3);
}

//------------------------------------------------------------------------
void ofxFern::draw_initial_rectangle(IplImage * frame, template_matching_based_tracker * tracker){
  draw_quadrangle(frame,
		  tracker->u0[0], tracker->u0[1],
		  tracker->u0[2], tracker->u0[3],
		  tracker->u0[4], tracker->u0[5],
		  tracker->u0[6], tracker->u0[7],
		  cvScalar(128), 3);
}

//------------------------------------------------------------------------
void ofxFern::draw_tracked_position(IplImage * frame, template_matching_based_tracker * tracker){
  draw_quadrangle(frame,
		  tracker->u[0], tracker->u[1],
		  tracker->u[2], tracker->u[3],
		  tracker->u[4], tracker->u[5],
		  tracker->u[6], tracker->u[7],
		  cvScalar(255), 3);
}

//------------------------------------------------------------------------
void ofxFern::draw_tracked_locations(IplImage * frame, template_matching_based_tracker * tracker){
  for(int i = 0; i < tracker->nx * tracker->ny; i++) {
    int x1, y1;
    tracker->f.transform_point(tracker->m[2 * i], tracker->m[2 * i + 1], x1, y1);
    cvCircle(frame, cvPoint(x1, y1), 3, cvScalar(255, 255, 255), 1);
  }
}

//------------------------------------------------------------------------
void ofxFern::draw_detected_keypoints(IplImage * frame, planar_pattern_detector * detector){
  for(int i = 0; i < detector->number_of_detected_points; i++)
    cvCircle(frame,
	     cvPoint(detector->detected_points[i].fr_u(),
		     detector->detected_points[i].fr_v()),
	     16 * (1 << int(detector->detected_points[i].scale)),
	     cvScalar(100), 1);
}

//------------------------------------------------------------------------
void ofxFern::draw_recognized_keypoints(IplImage * frame, planar_pattern_detector * detector){
  for(int i = 0; i < detector->number_of_model_points; i++)
    if (detector->model_points[i].class_score > 0)
      cvCircle(frame,
		cvPoint(detector->model_points[i].potential_correspondent->fr_u(),
		       detector->model_points[i].potential_correspondent->fr_v()),
	       16 * (1 << int(detector->detected_points[i].scale)),
	       cvScalar(255, 255, 255), 1);
}

//------------------------------------------------------------------------
void ofxFern::detect(IplImage * frame){
	
	// do we need to detect the marker?
	if(!bDetected){
	
		detector->detect(frame);
	
		// found the marker?
		if(detector->pattern_is_detected){
			bDetected = true;
			
			tracker->initialize(detector->detected_u_corner[0], detector->detected_v_corner[0],
					detector->detected_u_corner[1], detector->detected_v_corner[1],
					detector->detected_u_corner[2], detector->detected_v_corner[2],
					detector->detected_u_corner[3], detector->detected_v_corner[3]);
		}
		else{	// nope
			bDetected = false;
			trackedMarker.tracked = false;
			tracker->initialize();
			if(show_keypoints) {
				draw_detected_keypoints(frame, detector);
			}
			return;
		}
	}
	
	// track the marker if it was detected
	if(bDetected){
	
		// is the marker being tracked?
		if(tracker->track(frame)){
			if(show_keypoints) {
				draw_detected_keypoints(frame, detector);
				draw_recognized_keypoints(frame, detector);
			}
			setTrackedMarker(tracker);
			draw_tracked_position(frame, tracker);
			if(show_tracked_locations)
				draw_tracked_locations(frame, tracker);

		} else {	// nope
			if(show_keypoints) {
				draw_detected_keypoints(frame, detector);
				draw_recognized_keypoints(frame, detector);
			}
			setTrackedMarker(detector);
			draw_detected_position(frame, detector);
			bDetected = false;
		}
	}
	else{
		tracker->initialize();
		if(show_keypoints) {
			draw_detected_keypoints(frame, detector);
		}
		//draw_initial_rectangle(frame, tracker);
		trackedMarker.tracked = false;
	}
}

//------------------------------------------------------------------------
void ofxFern::setTrackedMarker(template_matching_based_tracker * tracker) {
	trackedMarker.points[0].set(tracker->u[0], tracker->u[1]);
	trackedMarker.points[1].set(tracker->u[2], tracker->u[3]);
	trackedMarker.points[2].set(tracker->u[4], tracker->u[5]);
	trackedMarker.points[3].set(tracker->u[6], tracker->u[7]);
	trackedMarker.tracked = true;
}

void ofxFern::setTrackedMarker(planar_pattern_detector * detector) {
	trackedMarker.points[0].set(detector->detected_u_corner[0], detector->detected_v_corner[0]);
	trackedMarker.points[1].set(detector->detected_u_corner[1], detector->detected_v_corner[1]);
	trackedMarker.points[2].set(detector->detected_u_corner[2], detector->detected_v_corner[2]);
	trackedMarker.points[3].set(detector->detected_u_corner[3], detector->detected_v_corner[3]);
	trackedMarker.tracked = true;
}
