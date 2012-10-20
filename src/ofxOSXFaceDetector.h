//
//  ofxOSXFaceDetector.h
//
//  Created by Kato Tetsuro on 12/10/19.
//
//

#ifndef __ofxOSXFaceDetector__
#define __ofxOSXFaceDetector__

#include <ofMain.h>

class FaceInfo {
public:
    bool hasLeftEye, hasRightEye, hasMouth;
    ofRectangle face;
    ofPoint leftEye, rightEye, mouth;
    void draw();
    void draw(float x, float y);
};


#ifdef __OBJC__
@class FaceDetector;
#endif

class ofxOSXFaceDetector {
private:
#ifdef __OBJC__
    FaceDetector *detector;
#else
    void         *detector;
#endif
    vector<FaceInfo> faces;
    
public:
    ofxOSXFaceDetector();
    ~ofxOSXFaceDetector();
    void findFaces(ofPixelsRef pixels);
    
    vector<FaceInfo> getFaces();
    int                 size();
    ofRectangle         getFace(int i);
    
    void                draw();
};

void convertTest(ofImage &src, ofImage &dst);


#endif /* defined(__ofxOSXFaceDetector__) */
