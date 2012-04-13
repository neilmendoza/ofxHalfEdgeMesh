#include "testApp.h"
#include "MeshUtils.h"

//--------------------------------------------------------------
void testApp::setup()
{
    lastUpdateTime = 0;
    for (int i = 0; i < NUM_TRIS * 3; ++i)
    {
        ofVec3f vertex(ofRandomf(), ofRandomf(), 0.1 * ofRandomf());
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
    
    cam.setNearClip(1e-4);
    cam.setDistance(2);
    
    light.setPosition(5, 0, 5);
    triMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    triMesh.buildEdgeData();
    itg::MeshUtils::instance().genNormals(triMesh);
    
    walkMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    halfEdges.push_back(triMesh.getHalfEdge(triMesh.getIndex(0)));
}

//--------------------------------------------------------------
void testApp::update()
{
    if (ofGetElapsedTimeMillis() - lastUpdateTime > 20 && walkMesh.getNumVertices() != triMesh.getNumIndices())
    {
        bool faceFound = false;
        while (!faceFound)
        {
            for (int i = 0; i < 3; ++i)
            {
                if (halfEdges.back()->getPair() && faces.find(halfEdges.back()->getPair()->getFace()) == faces.end())
                {
                    halfEdges.push_back(halfEdges.back()->getPair());
                    faces.insert(halfEdges.back()->getFace());
                    walkMesh.addVertex(triMesh.getVertex(halfEdges.back()->getVertexIdx()));
                    walkMesh.addVertex(triMesh.getVertex(halfEdges.back()->getNext()->getVertexIdx()));
                    walkMesh.addVertex(triMesh.getVertex(halfEdges.back()->getNext()->getNext()->getVertexIdx()));
                    itg::MeshUtils::instance().genNormals(walkMesh);
                    faceFound = true;
                    break;
                }
                halfEdges[halfEdges.size() - 1] = halfEdges[halfEdges.size() - 1]->getNext();
            }
            if (!faceFound) halfEdges.pop_back();
        }
        lastUpdateTime = ofGetElapsedTimeMillis();
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofSetColor(255, 255, 0);
    cam.begin();
    glRotatef(20 * ofGetElapsedTimef(), 0.5, 0, 1);
    light.disable();
    triMesh.drawWireframe();
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    light.enable();
    walkMesh.draw();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
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