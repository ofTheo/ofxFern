VER=1.1

EXECUTABLE_1_NAME = ferns_demo
SOURCES_1 = main mcv planar_pattern_detector planar_pattern_detector_builder \
            affine_transformation_range buffer_management pyr_yape06 homography06 homography_estimator \
            fine_gaussian_pyramid mcvGaussianSmoothing affine_image_generator06 fern_based_point_classifier \
            ferns template_matching_based_tracker cmphomo

HEADERS= affine_image_generator06.h affine_transformation_range.h buffer_management.h \
cmphomo.h fern_based_point_classifier.h ferns.h fine_gaussian_pyramid.h \
general.h homography06.h homography_estimator.h keypoint.h mcvGaussianSmoothing.h \
mcv.h planar_pattern_detector_builder.h planar_pattern_detector.h pyr_yape06.h \
template_matching_based_tracker.h

CC = g++
LINK = g++

# DEBUG_OPTIM = -g 
DEBUG_OPTIM = -O3
WARNINGS = -Wall -Wextra

OPENCV_INC = `pkg-config opencv --cflags`
ALL_LIBS_INCLUDE = $(OPENCV_INC)

OPENCV_LIB = `pkg-config opencv --libs`

ALL_LIBS_LIB = $(OPENCV_LIB) -lz

CC_OPTIONS =  $(WARNINGS) $(DEBUG_OPTIM) $(ALL_LIBS_INCLUDE)
LINK_OPTIONS = $(ALL_LIBS_LIB)


all: $(EXECUTABLE_1_NAME) $(EXECUTABLE_2_NAME)

SOURCES_1_CC = $(SOURCES_1:=.cc)
SOURCES_1_OBJ = $(SOURCES_1:=.o)

SOURCES_2_CC = $(SOURCES_2:=.cc)
SOURCES_2_OBJ = $(SOURCES_2:=.o)

$(EXECUTABLE_1_NAME): $(SOURCES_1_OBJ)
	$(LINK) $(SOURCES_1_OBJ) $(LINK_OPTIONS) -o $(EXECUTABLE_1_NAME)

$(EXECUTABLE_2_NAME): $(SOURCES_2_OBJ)
	$(LINK) $(SOURCES_2_OBJ) $(LINK_OPTIONS) -o $(EXECUTABLE_2_NAME)

.cc.o:
	$(CC) $(CC_OPTIONS) -c $*.cc

dep: depend.inc
depend.inc:
	g++ -MM $(ALL_LIBS_INCLUDE) $(SOURCES_1_CC) $(SOURCES_2_CC) > depend.inc

clean:
	@rm -f *~ *.o depend.inc


DIST_FILES= $(SOURCES_1_CC) $(SOURCES_2_CC) $(HEADERS) \
Makefile Makefile.icc model.bmp model.bmp.roi \
COPYING README AUTHORS

DIST_FN=ferns_demo-$(VER)
DIST_V_FN=ferns_demo_v-$(VER)

dist:
	mkdir /tmp/$(DIST_FN)
	cp $(DIST_FILES) /tmp/$(DIST_FN)
	tar -czf $(DIST_FN).tar.gz -C /tmp $(DIST_FN)
	rm -fR /tmp/$(DIST_FN)

dist-video:
	mkdir /tmp/$(DIST_FN)
	cp $(DIST_FILES) mousepad.mp4 /tmp/$(DIST_FN)
	tar -czf $(DIST_V_FN).tar.gz -C /tmp $(DIST_FN)
	rm -fR /tmp/$(DIST_FN)



include depend.inc
