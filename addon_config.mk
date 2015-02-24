meta:
	ADDON_NAME = ofxFern
	ADDON_DESCRIPTION = An implementation of the Fern tracker from EPFL CVLab for OpenFrameworks.
	ADDON_AUTHOR = Theodore Watson
	ADDON_URL = https://github.com/ofTheo/ofxFern

common:
	ADDON_DEPENDENCIES = ofxOpenCv
	# Include zlib headers for Windows (zlib libraries are included in ofxOpenCv)
	ADDON_INCLUDES += include
	ADDON_SOURCES_EXCLUDE = AUTHORS COPYING README
	ADDON_SOURCES_EXCLUDE += Makefile Makefile.icc
	ADDON_SOURCES_EXCLUDE += model.bmp model.bmp.roi
