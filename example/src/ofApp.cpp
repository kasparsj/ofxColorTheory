#include "ofApp.h"
#include "ColorWheelSchemes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    group.setName("Color Theory");
    group.add(primaryColor.set("Primary Color", ofColor::magenta));
    group.add(colorScheme.set("Color Scheme", 6, 0, ColorWheelSchemes::SCHEMES.size()-1));
    group.add(colorSchemeName);
    group.add(numColors.set("Num Colors", 256, 1, 256));
    
    panel.setup();
    panel.add(group);
}

//--------------------------------------------------------------
void ofApp::update() {
    colorSchemeName.set(ColorWheelSchemes::NAMES.at(colorScheme.get()));
    scheme = ColorWheelSchemes::SCHEMES.at(colorScheme.get());
    scheme->setPrimaryColor(primaryColor.get());
    colors = scheme->interpolate(numColors.get());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushStyle();
    float w = ofGetWidth() / (float) colors.size();
    for (int i=0; i<colors.size(); i++) {
        ofSetColor(colors[i]);
        ofFill();
        ofDrawRectangle(w * i, 0, w, ofGetHeight());
    }
    ofPopStyle();
    
    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key >= '1' && key < '1' + ColorWheelSchemes::SCHEMES.size()) {
        colorScheme.set(key - '1');
    }
    //else if (key == 's') {
        //ofSaveFrame();
    //}
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
