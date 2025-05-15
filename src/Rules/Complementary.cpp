#include "Complementary.h"
#include "ColorUtil.h"

namespace ofxColorTheory {

template<typename T>
void Complementary_<T>::generate() {
    // original
    this->colors.push_back(this->primaryColor);
    
    // A contrasting color: much darker or lighter than the original
    T contrasting = T(this->primaryColor);
    this->colors.push_back(adjust(contrasting, 0.4f));
    
    // A soft supporting color: lighter and less saturated
    T supporting = T(this->primaryColor);
    supporting.setBrightness(0.3f*255.f + this->primaryColor.getBrightness());
    supporting.setSaturation(0.1f*255.f + this->primaryColor.getSaturation() * 0.3f);
    this->colors.push_back(supporting);
    
    T complement = getComplement();
    
    // A contrasting complement: very dark or very light
    T contrastingComplement = T(complement);
    this->colors.push_back(adjust(contrastingComplement, 0.3f));
    
    // The complment
    this->colors.push_back(complement);
    
    // A light supporting variant
    T supportingComplement = T(complement);
    supportingComplement.setBrightness(0.3f*255.f + complement.getBrightness());
    supportingComplement.setSaturation(0.1f*255.f + complement.getSaturation() * 0.25f);
    this->colors.push_back(supportingComplement);
}

template<typename T>
T Complementary_<T>::adjust(T target, float threshold) {
    if(target.getBrightness() > threshold*255.0) {
        target.setBrightness(0.1f*255.f + target.getBrightness() * 0.25f);
    } else {
        target.setBrightness(255.f - target.getBrightness() * 0.25f);
    }
    return target;
}

template<typename T>
T Complementary_<T>::getComplement() {
    return ColorUtil::rybRotate(this->primaryColor, 180);
}

template<typename T>
std::vector<T> Complementary_<T>::interpolate(int steps, std::vector<T> &colors) {
    std::vector<T> result;
    int pri = colors.size();
    int add = steps - pri;
    int each = ceil((float) add/(pri-2));
    int pri_steps = std::min(pri, steps);
    for (int i=0; i<pri_steps; i++) {
        result.push_back(colors.at(i));
        int space = steps - result.size();
        if (space > (pri_steps - (i+1)) && i != 2) {
            for (int j=0; j<std::min(each, space); j++) {
                T color = ColorUtil::lerpLch(colors.at(i), colors.at(i+1), (float) (j+1)*1/(each+1));
                result.push_back(color);
            }
        }
    }
    return result;
}

}
