#include "Tetrad.h"
#include "ColorUtil.h"

namespace ofxColorTheory {

template<typename T>
void Tetrad_<T>::generate() {
    this->colors.push_back(this->primaryColor);
    float limit = T::limit();
    float bri = this->primaryColor.getBrightness()/limit;
    
    T c1 = ColorUtil::rybRotate(this->primaryColor, angle);
    float multiplier;
    if(!alt)
    {
        if(bri < .5f) {
            c1.setBrightness((bri+.2f)*limit);
        } else {
            c1.setBrightness((bri-.2f)*limit);
        }
    } else {
        multiplier = (.5f-bri)/.5f;
        c1.setBrightness(bri+MIN(.2f, MAX(-.2f,.2f*multiplier)));
    }
    
    this->colors.push_back(c1);
    
    T c2 = ColorUtil::rybRotate(this->primaryColor, angle * 2);
    if(!alt)
    {
        if(bri > .5f) {
            c2.setBrightness((bri+.1f)*limit);
        } else {
            c2.setBrightness((bri-.1f)*limit);
        }
    } else {
        multiplier = (.5f-bri)/.5f;
        c2.setBrightness(bri+MIN(.1f, MAX(-.1f,.1f*multiplier)));
    }
    
    this->colors.push_back(c2);
    
    ofColor c3 = ColorUtil::rybRotate(this->primaryColor, angle * 3);
    c3.setBrightness((bri+.1f)*limit);
    this->colors.push_back(c3);
}

template class Tetrad_<ofColor>;
template class Tetrad_<ofFloatColor>;

}
