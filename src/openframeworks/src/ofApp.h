#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void saveCanvas();

    
    //int BLEND_MODE = LIGHTEST;
    bool IS_FLIPPED = true;
    bool IS_RESETED = true;
    
    ofVideoGrabber cam;
    unsigned char * videoAlpha;
    ofTexture videoTexture;
    
    //PImage canvas, canvas_back;
    ofImage canvas_back;
    
    int captureWidth = 640;
    int captureHeight = 480;
    int captureX = 0;
    int captureY = 0;
    int brightThreshold, alphaThreshold;
		
};
