#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_NOTICE);
    vidGrabber.initGrabber(320, 240);
}

//--------------------------------------------------------------
void testApp::update(){
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
        detector.findFaces(vidGrabber.getPixelsRef());
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    vidGrabber.draw(0, 0);
    
    ofNoFill();
    int size = detector.size();
    detector.draw();

    ofDrawBitmapString("numFace:" + ofToString(size), 20, 255);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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