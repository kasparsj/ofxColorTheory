#include "FlippedCompound.h"
#include "../ColorUtil.h"

namespace ofxColorTheory {

template<typename T>
void FlippedCompound_<T>::generate() {
    this->colors.push_back(this->primaryColor);
    float limit = T::limit();
    float sat = this->primaryColor.getSaturation()/limit;
    float bri = this->primaryColor.getBrightness()/limit;
    
    T c1 = ColorUtil::rybRotate(this->primaryColor, -30);
    c1.setBrightness(this->wrap(bri, .25f, .6f, .25f)*limit);
    this->colors.push_back(c1);
    
    T c2 = ColorUtil::rybRotate(this->primaryColor, -30);
    c2.setBrightness(this->wrap(bri, .4f, .1f, .4f)*limit);
    c2.setSaturation(this->wrap(sat, .4f, .2f, .4f)*limit);
    this->colors.push_back(c2);
    
    T c3 = ColorUtil::rybRotate(this->primaryColor, -160);
    c3.setBrightness(std::max(.2f, bri)*limit);
    c3.setSaturation(this->wrap(sat, .25f, .1f, .25f)*limit);
    this->colors.push_back(c3);
    
    T c4 = ColorUtil::rybRotate(this->primaryColor, -150);
    c4.setBrightness(this->wrap(bri, .3f, .6f, .3f)*limit);
    c4.setSaturation(this->wrap(sat, .1f, .8f, .1f)*limit);
    this->colors.push_back(c4);
    
    T c5 = ColorUtil::rybRotate(this->primaryColor, -150);
    c5.setBrightness(this->wrap(bri, .4f, .2f, .4f)*limit);
    c5.setSaturation(this->wrap(sat, .1f, .8f, .1f)*limit);
    this->colors.push_back(c5);
}

}
