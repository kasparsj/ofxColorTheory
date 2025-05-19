#include "ofApp.h"
#include "ColorWheelSchemes.h"

namespace ofxColorTheory {

template class Analogous_<ofColor>;
template class Complementary_<ofColor>;
template class Compound_<ofColor>;
template class FlippedCompound_<ofColor>;
template class Monochrome_<ofColor>;
template class SplitComplementary_<ofColor>;
template class Tetrad_<ofColor>;
template class Triad_<ofColor>;

template<>
const std::vector<std::shared_ptr<ColorWheelScheme_<ofColor>>> ColorWheelSchemes_<ofColor>::SCHEMES = ColorWheelSchemes_<ofColor>::createColorSchemes();
}

//--------------------------------------------------------------
void ofApp::setup(){
    group.setName("Color Theory");
    group.add(primaryColor.set("Primary Color", ofColor::magenta));
    group.add(colorScheme.set("Color Scheme", 6, 0, ColorWheelSchemes_<ofColor>::SCHEMES.size()-1));
    group.add(colorSchemeName);
    group.add(colorSpace.set("Color Space", 2, 0, 2));
    group.add(colorSpaceName);
    group.add(numColors.set("Num Colors", 256, 1, 256));
    
    panel.setup();
    panel.add(group);
}

//--------------------------------------------------------------
void ofApp::update() {
    std::string newName = ColorWheelSchemes_<ofColor>::NAMES.at(colorScheme.get());
    std::string newSpace = colorSpaces.at(colorSpace.get());
    ofColor newColor = primaryColor.get();
    int newCount = numColors.get();
    if (colorSchemeName.get() != newName || colorSpaceName.get() != newSpace ||
        scheme->getPrimaryColor() != newColor || colors.size() != newCount) {
        colorSchemeName.set(newName);
        colorSpaceName.set(newSpace);
        scheme = ColorWheelSchemes_<ofColor>::SCHEMES.at(colorScheme.get());
        scheme->setPrimaryColor(newColor);
        scheme->regenerate();
        colors = scheme->interpolate(newCount, colorSpace.get());
    }
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
    if (key >= '1' && key < '1' + ColorWheelSchemes_<ofColor>::SCHEMES.size()) {
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
