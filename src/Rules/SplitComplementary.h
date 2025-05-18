#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
 
    template<typename T>
    class SplitComplementary_ : public ColorWheelScheme_<T> {
        
    public:
        SplitComplementary_() : ColorWheelScheme_<T>() {
            
        }
        SplitComplementary_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        std::vector<T>& generate() {
            this->colors.push_back(this->primaryColor);
            float limit = T::limit();
            float bri = this->primaryColor.getBrightness()/limit;
            
            T c1 = ColorUtil::rybRotate(this->primaryColor, 150);
            T c2 = ColorUtil::rybRotate(this->primaryColor, 210);
            
            c1.setBrightness((bri+.1f)*limit);
            c2.setBrightness((bri+.1f)*limit);
            
            this->colors.push_back(c1);
            this->colors.push_back(c2);
            
            return this->colors;
        }
        
    };
    
}
