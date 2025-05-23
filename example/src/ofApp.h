#pragma once

#include "ofMain.h"
#include "ColorWheelScheme.h"
#include "ofxGui.h"

using namespace ofxColorTheory;
using namespace std;

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    shared_ptr<ColorWheelScheme_<ofColor>> scheme;
    vector<ofColor> colors;
    
    ofxPanel panel;
    ofParameterGroup group;
    ofParameter<ofColor> primaryColor;
    ofParameter<int> colorScheme;
    ofReadOnlyParameter<string, ofApp> colorSchemeName;
    ofParameter<int> colorSpace;
    ofReadOnlyParameter<string, ofApp> colorSpaceName;
    ofParameter<int> numColors;
		
    std::vector<string> colorSpaces = {"RGB", "HSB", "CIELCh"};
};
