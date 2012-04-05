ofxFern
===========

An implementation of the Fern tracker from EPFL CVLab for OpenFrameworks.

See Documentation on [Github](https://github.com/ofTheo/ofxFern).

OpenFrameworks is a cross platform open source toolkit for creative coding in C++.

[http://www.openframeworks.cc/](http://www.openframeworks.cc/)

Description
-----------

ofxFern is an addon for doing 2D "markerless tracking" using an image as the marker using the ferns library. See [Ferns: Planar Object Detection Demo](http://cvlab.epfl.ch/software/ferns/index.php).

Installation
------------

To use ofxFern, first you need to download and install Open Frameworks.

To get a copy of the repository you can download the source from [http://github.com/ofTheo/ofxFern/zipball/master](http://github.com/ofTheo/ofxFern/zipball/master) or, alternatively, you can use git clone:
<pre>
git clone git://github.com/ofTheo/ofxFern.git
</pre>

The addon should sit in `openFrameworks/addons/ofxFern/`.

You will also need the following addon dependencies:

* ofxOpenCV: included with OpenFrameworks

Running the Example Project
-------------------------------

If you're using OS X, open the Xcode project in ofxFern/ofxFernCameraDemo/ and hit "Build and Run".

The addon should work fine in Windows and Linux, although there are no example build files yet.

Adding ofxFern to an Existing Project
---------------------------------------

If you want to add ofxFern to another project, you need to make sure you include the src folders:
<pre>
openFrameworks/addons/ofxFern/src
</pre>

For Xcode:

* create a new group "ofxFern"
* drag these directories from ofxFern into this new group: ofxFern/src
* you also need to add the following addon dependencies in a similar manner:
	* ofxOpenCV

DEVELOPING
----------

You can help develop ofxFern on GitHub: [https://github.com/ofTheo/ofxFern](https://github.com/ofTheo/ofxFerb)

Create an account, clone or fork the repo, then request a push/merge.

If you find any bugs or suggestions please log them to GitHub as well.
