#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetVerticalSync(true);
    ofSetVerticalSync(true);
    
    IS_FLIPPED = true;
    IS_RESETED = true;
    captureWidth = 640;
    captureHeight = 480;
    brightThreshold = 200;
    alphaThreshold = 75;
    scaleRatio = float(ofGetWindowWidth())/float(captureWidth);

    cam.setDeviceID(0);
    cam.setDesiredFrameRate(30);
    cam.initGrabber(captureWidth, captureHeight);
    
    videoAlpha   = new unsigned char[captureWidth*captureHeight*4];
    videoTexture.allocate(captureWidth,captureHeight, GL_RGBA);

    ofBackground(0);
    ofSetBackgroundAuto(false);

    // ofSetBackgroundAuto not working in Raspberry Pi 2
#ifdef TARGET_RASPBERRY_PI
    ping = new ofFbo();
    pong = new ofFbo();
    ping->allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 0);
    pong->allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 0);
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
    int r,g,b,a;
    cam.update();
    if(cam.isFrameNew()) {
        int totalPixels = captureWidth*captureHeight;
        unsigned char * pixels = cam.getPixels();
        for (int i = 0; i < totalPixels; i++){
            r = pixels[i*3];
            g = pixels[i*3+1];
            b = pixels[i*3+2];
            a = alphaThreshold;
  
            if (r<=brightThreshold) r = 0;
            if (g<=brightThreshold) g = 0;
            if (b<=brightThreshold) b = 0;
            
            videoAlpha[i*4] = r;
            videoAlpha[i*4+1] = g;
            videoAlpha[i*4+2] = b;
            videoAlpha[i*4+3] = a;
        }
        videoTexture.loadData(videoAlpha, captureWidth,captureHeight, GL_RGBA);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (IS_RESETED) {
        ofBackground(0); IS_RESETED = false;
        #ifdef TARGET_RASPBERRY_PI
          ping->begin(); ofClear(0,0,0,0); ping->end();
          pong->begin(); ofClear(0,0,0,0); pong->end();
        #endif
    }

#ifdef TARGET_RASPBERRY_PI
    ping->begin();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    pong->draw(0,0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    videoTexture.draw(0,(ofGetWindowHeight()-(captureHeight * scaleRatio)), ofGetWindowWidth(), captureHeight * scaleRatio);
    ofDisableBlendMode();
    ping->end();
#else 
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
#endif
    
    ofPushMatrix();
    if (IS_FLIPPED) {
        ofScale( -1, 1, 1 ); // flip side
        ofTranslate(-ofGetWindowWidth(), 0, 0);
    }

#ifdef TARGET_RASPBERRY_PI
    ping->draw(0,0);
    ofFbo* temp = ping;
    ping = pong;
    pong = temp;
#else
    videoTexture.draw(0,(ofGetWindowHeight()-(captureHeight * scaleRatio)), ofGetWindowWidth(), captureHeight * scaleRatio);
    ofDisableBlendMode();
#endif
    ofPopMatrix();
    return;
}

void ofApp::saveCanvas()
{
    canvas_back.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    string image_name = "./"+ofToString(ofGetYear())+ofToString(ofGetMonth())+ofToString(ofGetDay())+ofToString(ofGetHours())+ofToString(ofGetMinutes())+ofToString(ofGetSeconds())+".png";
    canvas_back.saveImage(image_name);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            //ofToggleFullscreen();
            IS_FLIPPED = !IS_FLIPPED;
            break;
        case ' ':
            saveCanvas();
            IS_RESETED = true;
            break;
        case 's':
            saveCanvas();
            break;
        case OF_KEY_DOWN:
            brightThreshold -=1;
            if (brightThreshold <= 0) brightThreshold = 0;
            ofLog() << "Cam Bright Threshold: " << brightThreshold;
            break;
        case OF_KEY_UP:
            brightThreshold +=1;
            if (brightThreshold >= 255) brightThreshold = 255;
            ofLog() << "Cam Bright Threshold: " << brightThreshold;
            break;
        case OF_KEY_LEFT:
            alphaThreshold -=1;
            if (alphaThreshold <= 0) alphaThreshold = 0;
            ofLog() << "Cam Alpha Threshold: " << alphaThreshold;
            break;
        case OF_KEY_RIGHT:
            alphaThreshold +=1;
            if (alphaThreshold >= 255) alphaThreshold = 255;
            ofLog() << "Cam Alpha Threshold: " << alphaThreshold;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
