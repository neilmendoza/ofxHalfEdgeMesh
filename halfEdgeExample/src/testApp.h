#pragma once

#include "ofMain.h"
#include "ofxHalfEdgeMesh.h"
#include "ofxDelaunay.h"

class testApp : public ofBaseApp
{
public:
    static const int NUM_TRIS = 30;
    static const int NUM_VERTS = 3 * NUM_TRIS;
    
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
    ofxHem::IndexedTriMesh triMesh;
    ofxDelaunay delaunay;
    ofLight light;
    ofEasyCam cam;
};
