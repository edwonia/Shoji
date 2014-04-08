#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOpenCv.h"
#include "ofxQuadWarp.h"

#include "QuadSurface.h"

class testApp : public ofBaseApp{

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
    
        void debugUpdate();
        void debugDraw();
    
        void mainUpdate();
    
        // GUI VARIABLES
        ofxUISuperCanvas *debugGUI;
        ofxUISuperCanvas *gui;
        void exit();
        void guiEvent(ofxUIEventArgs &e);
    
	private:
		void setupGui();

	private:

		QuadSurface m_quadSurface;

		ofVideoGrabber 		vidGrabber;

        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;

        bool                debug;
        bool                showIR;
        bool                showQuad;
		int 				threshold;
        float               thresholdFloat;
        int                 blobsTotal;
        float               blobsTotalFloat;
		bool				bLearnBakground;
        float               minBlobSize;


};

