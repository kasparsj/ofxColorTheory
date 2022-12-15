#include "Triad.h"
#include "ColorUtil.h"

namespace ofxColorTheory {

template<typename T>
void Triad_<T>::generate() {
    this->colors.push_back(this->primaryColor);
    float limit = T::limit();
    float bri = this->primaryColor.getBrightness()/limit;
    
    T c1 = ColorUtil::rybRotate(this->primaryColor, angle);
    c1.setBrightness((bri+.1f)*limit);
    this->colors.push_back(c1);
    
    T c2 = ColorUtil::rybRotate(this->primaryColor, -angle);
    c2.setBrightness((bri+.1f)*limit);
    this->colors.push_back(c2);
}

template class Triad_<ofColor>;
template class Triad_<ofFloatColor>;


}
