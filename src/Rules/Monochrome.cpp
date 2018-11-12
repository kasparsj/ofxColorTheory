#include "Monochrome.h"

using namespace ofxColorTheory;

void Monochrome::generate() {
    colors.push_back(primaryColor);

    ofColor c1 = ofColor(primaryColor);
    c1.setBrightness(wrap(primaryColor.getBrightness()/255.f, .50f, .20f, .30f)*255.f);
    c1.setSaturation(wrap(primaryColor.getSaturation()/255.f, .30f, .10f, .20f)*255.f);
    colors.push_back(c1);

    ofColor c2 = ofColor(primaryColor);
    c2.setBrightness(wrap(primaryColor.getBrightness()/255.f, .20f, .20f, .60f)*255.f);
    colors.push_back(c2);

    ofColor c3 = ofColor(primaryColor);
    c3.setBrightness(fmax(.20f*255.f, primaryColor.getBrightness() + (255.f - primaryColor.getBrightness() ) * 0.2f));
    c3.setSaturation(wrap(primaryColor.getSaturation()/255.f, .30f, .10f, .30f)*255.f);
    colors.push_back(c3);

    ofColor c4 = ofColor(primaryColor);
    c4.setBrightness(wrap(primaryColor.getBrightness()/255.f, .50f, .20f, .30f)*255.f);
    colors.push_back(c4);
}
