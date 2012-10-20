#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(30);
    ofSetWindowShape(640, 500);
    
    deviceId = 0;
    vidGrabber.setDeviceID(deviceId);
    vidGrabber.initGrabber(320, 240);
    
    classifier.load(ofToDataPath("haarcascade_frontalface_alt2.xml"));
	scaleFactor = 0.5;
	// shouldn't need to allocate, resize should do this for us
	graySmall.allocate(vidGrabber.getWidth() * scaleFactor, vidGrabber.getHeight() * scaleFactor, OF_IMAGE_GRAYSCALE);
}

//--------------------------------------------------------------
void testApp::update(){
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
        detector.findFaces(vidGrabber.getPixelsRef());
        
        
        ofxCv::convertColor(vidGrabber, gray, CV_RGB2GRAY);
        ofxCv::resize(gray, graySmall);
        cv::Mat graySmallMat = ofxCv::toCv(graySmall);
		if(ofGetMousePressed()) {
            cv::equalizeHist(graySmallMat, graySmallMat);
		}
		graySmall.update();
		
		classifier.detectMultiScale(graySmallMat, objects, 1.06, 1,
                                    //CascadeClassifier::DO_CANNY_PRUNING |
                                    //CascadeClassifier::FIND_BIGGEST_OBJECT |
                                    //CascadeClassifier::DO_ROUGH_SEARCH |
                                    0);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    vidGrabber.draw(0, 0);
    
    ofNoFill();
    int size = detector.size();
    detector.draw();

    ofDrawBitmapString("numFace:" + ofToString(size), 20, 255);
    
	
    ofTranslate(320, 0);
    vidGrabber.draw(0, 0);
	ofScale(1 / scaleFactor, 1 / scaleFactor);
	for(int i = 0; i < objects.size(); i++) {
		ofRect(ofxCv::toOf(objects[i]));
	}
	
	ofDrawBitmapString(ofToString(objects.size()), 10, 20);
    ofTranslate(-320, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_LEFT:
            vidGrabber.close();
            vidGrabber.setDeviceID(--deviceId);
            vidGrabber.initGrabber(320, 240);
            break;
        case OF_KEY_RIGHT:
            vidGrabber.close();
            vidGrabber.setDeviceID(++deviceId);
            vidGrabber.initGrabber(320,240);
        default:
            break;
    }
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