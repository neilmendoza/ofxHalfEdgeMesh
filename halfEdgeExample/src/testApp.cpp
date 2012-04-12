#include "testApp.h"
#include "MeshUtils.h"

//--------------------------------------------------------------
void testApp::setup()
{
    for (int i = 0; i < NUM_TRIS * 3; ++i)
    {
        ofVec3f vertex(ofRandomf(), ofRandomf(), 0.02 * ofRandomf());
        //cout << i << ": " << vertex << endl;
        delaunay.addPoint(vertex);
    }
    delaunay.triangulate();
    vector<ofxDelaunayTriangle> tris = delaunay.triangles;
    
    // extract indices
    ofVec3f vertices[NUM_VERTS];
    for (int i = 0; i < tris.size(); ++i)
    {
        for (int j = 2; j >= 0; --j)
        {
            vertices[tris[i].pointIndex[j]] = tris[i].points[j];
            triMesh.addIndex(tris[i].pointIndex[j]);
        }
    }
    
    // add vertices
    triMesh.addVertices(vertices, NUM_VERTS);
    
    /*
    // add indices
    for (int i = 0; i < tris.size(); ++i)
    {
        cout << "triangle " << i << endl;
        
        for (int j = 0; j < 3; ++j)
        {
            triMesh.addIndex(tris[i].pointIndex[j]);
            //triMesh.addVertex(tris[i].points[j]);
            //triMesh.addNormal(normal);
            cout << tris[i].points[j] << ", " << tris[i].pointIndex[j] << endl;
        }
        
        cout << endl;
    }
     */
    
    cam.setNearClip(1e-4);
    cam.setDistance(2);
    
    light.setPosition(5, 0, 5);
    light.enable();
    triMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    triMesh.buildEdgeData();
    itg::MeshUtils::instance().genNormals(triMesh);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw()
{
    ofSetColor(255, 255, 0);
    cam.begin();
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    triMesh.draw();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    ofDrawAxis(0.5);

    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}