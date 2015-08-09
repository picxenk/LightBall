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

    
    bool IS_FLIPPED;
    bool IS_RESETED;
    
    ofVideoGrabber cam;
    unsigned char * videoAlpha;
    ofTexture videoTexture;
    
    ofImage canvas;
    ofImage canvas_back;
    
    int captureWidth;
    int captureHeight;
    int brightThreshold, alphaThreshold;

    float scaleRatio;

#ifdef TARGET_RASPBERRY_PI
    ofFbo* ping;
    ofFbo* pong;
#endif
};
