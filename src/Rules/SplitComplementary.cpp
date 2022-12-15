#include "SplitComplementary.h"
#include "ColorUtil.h"

namespace ofxColorTheory {

template<typename T>
void SplitComplementary_<T>::generate() {
    this->colors.push_back(this->primaryColor);
    float limit = ofColor::limit();
    float bri = this->primaryColor.getBrightness()/limit;
    
    T c1 = ColorUtil::rybRotate(this->primaryColor, 150);
    T c2 = ColorUtil::rybRotate(this->primaryColor, 210);
    
    c1.setBrightness((bri+.1f)*limit);
    c2.setBrightness((bri+.1f)*limit);
    
    this->colors.push_back(c1);
    this->colors.push_back(c2);
}

template class SplitComplementary_<ofColor>;
template class SplitComplementary_<ofFloatColor>;

}
