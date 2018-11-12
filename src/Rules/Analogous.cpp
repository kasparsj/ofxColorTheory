#include "Analogous.h"
#include "ColorUtil.h"

using namespace ofxColorTheory;

void Analogous::generate() {
    colors.push_back(primaryColor);
    ofColor newColor;
    float array[4][2] = {{1.0, 2.2}, {2.0, 1.0}, {-1.0, -0.5}, {-2.0, 1.0}};
    for (int i=0; i<4; i++) {
        float one = array[i][0];
        float two = array[i][1];

        newColor = ColorUtil::rybRotate(primaryColor, angle * one);
        float t = 0.44f - two * 0.1f;
        float newBri = primaryColor.getBrightness()/255.f - contrast/100.f * two;
        if(newBri < t) {
            newColor.setBrightness(t * 255.f);
        } else {
            newColor.setBrightness(newBri*255.f);
        }
        newColor.setSaturation(newColor.getSaturation()-0.05f*255.f);
        colors.push_back(newColor);
    }
}
