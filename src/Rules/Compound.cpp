#include "Compound.h"
#include "ColorUtil.h"

using namespace ofxColorTheory;

void Compound::generate() {
    colors.push_back(primaryColor);

    ofColor c1 = ColorUtil::rybRotate(primaryColor, 30);
    c1.setBrightness(wrap(primaryColor.getBrightness()/255.f, .25f, .60f, .25f)*255.f);
    colors.push_back(c1);

    ofColor c2 = ColorUtil::rybRotate(primaryColor, 30);
    c2.setBrightness(wrap(primaryColor.getBrightness()/255.f, .40f, .10f, .40f)*255.f);
    c2.setSaturation(wrap(primaryColor.getSaturation()/255.f, .40f, .20f, .40f)*255.f);
    colors.push_back(c2);

    ofColor c3 = ColorUtil::rybRotate(primaryColor, 160);
    c3.setBrightness(fmax(.20f, primaryColor.getBrightness()/255.f)*255.f);
    c3.setSaturation(wrap(primaryColor.getSaturation()/255.f, .25f, .10f, .25f)*255.f);
    colors.push_back(c3);

    ofColor c4 = ColorUtil::rybRotate(primaryColor, 150);
    c4.setBrightness(wrap(primaryColor.getBrightness()/255.f, .30f, .60f, .30f)*255.f);
    c4.setSaturation(wrap(primaryColor.getSaturation()/255.f, .10f, .80f, .10f)*255.f);
    colors.push_back(c4);

    ofColor c5 = ColorUtil::rybRotate(primaryColor, 150);
    c5.setBrightness(wrap(primaryColor.getBrightness()/255.f, .40f, .20f, .40f)*255.f);
    c5.setSaturation(wrap(primaryColor.getSaturation()/255.f, .10f, .80f, .10f)*255.f);
    colors.push_back(c5);
}
