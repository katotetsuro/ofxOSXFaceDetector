//
//  ofxOSXFaceDetector.mm
//
//  Created by Kato Tetsuro on 12/10/19.
//
//

#include "ofxOSXFaceDetector.h"
#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>

@interface FaceDetector : NSObject {
    CIDetector *detector;
}

- (NSArray*) findFaces:(CIImage*)image;


@end

@implementation FaceDetector
- (id) init
{
    if (self = [super init]) {
        ofLogNotice("init");
        detector = [CIDetector detectorOfType:CIDetectorTypeFace context:nil options:[NSDictionary dictionaryWithObject:CIDetectorAccuracyHigh forKey:CIDetectorAccuracy]];
    }
    return self;
}

- (NSArray*) findFaces:(CIImage*)image
{
    return [detector featuresInImage:image];
}
@end


void FaceInfo::draw() {
    ofSetColor(ofColor::blue);
    ofRect(face);
    ofSetColor(ofColor::yellow);
    ofCircle(leftEye, 10);
    ofCircle(rightEye, 10);
    ofSetColor(ofColor::red);
    ofCircle(mouth, 10);
    ofSetColor(ofColor::white);
}

void FaceInfo::draw(float x, float y) {
    
}

CIImage* getCIImage(ofPixelsRef pixels) {
    unsigned char * pixelsPtr = pixels.getPixels();
    NSBitmapImageRep *rep = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:&pixelsPtr pixelsWide:pixels.getWidth() pixelsHigh:pixels.getHeight() bitsPerSample:8 samplesPerPixel:3 hasAlpha:NO isPlanar:NO colorSpaceName:NSDeviceRGBColorSpace bitmapFormat:NSAlphaNonpremultipliedBitmapFormat bytesPerRow:3*pixels.getWidth() bitsPerPixel:24];
    CIImage *ciImage = [[CIImage alloc] initWithBitmapImageRep:rep];
    
    return ciImage;
}

ofxOSXFaceDetector::ofxOSXFaceDetector() {
    detector = [[FaceDetector alloc] init];
}

ofxOSXFaceDetector::~ofxOSXFaceDetector() {
    [detector dealloc];
}

void ofxOSXFaceDetector::findFaces(ofPixelsRef pixels) {
    CIImage *ciImage = getCIImage(pixels);
    NSArray* facesArray = [detector findFaces:ciImage];
    faces.clear();
    for (CIFaceFeature* faceFeature in facesArray) {
        FaceInfo info;
        
        // flip y-axis
        int y = pixels.getHeight();
        // face
        info.face.width = faceFeature.bounds.size.width;
        info.face.height = faceFeature.bounds.size.height;
        info.face.x = faceFeature.bounds.origin.x;
        info.face.y = y/2 - faceFeature.bounds.origin.y;
        // eye
        if ( (info.hasLeftEye = faceFeature.hasLeftEyePosition) == true) {
            info.leftEye.x = faceFeature.leftEyePosition.x;
            info.leftEye.y = y - faceFeature.leftEyePosition.y;
            
        }
        if ( (info.hasRightEye = faceFeature.hasRightEyePosition) == true) {
            info.rightEye.x = faceFeature.rightEyePosition.x;
            info.rightEye.y = y - faceFeature.rightEyePosition.y;
        }
        // mouth
        if ( (info.hasMouth = faceFeature.hasMouthPosition) == true) {
            info.mouth.x = faceFeature.mouthPosition.x;
            info.mouth.y = y - faceFeature.mouthPosition.y;
        }
        
        faces.push_back(info);
    }
}

vector<FaceInfo> ofxOSXFaceDetector::getFaces() {
    return faces;
}

int ofxOSXFaceDetector::size() {
    return faces.size();
}

ofRectangle ofxOSXFaceDetector::getFace(int i) {
    return faces[i].face;
}

void ofxOSXFaceDetector::draw() {
    for (vector<FaceInfo>::iterator it=faces.begin();
         it!=faces.end(); ++it) {
        it->draw();
    }
}