#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class Monochrome_ : public ColorWheelScheme_<T> {
        
    public:
        Monochrome_() : ColorWheelScheme_<T>() {
            
        }
        Monochrome_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate() {
            this->colors.push_back(this->primaryColor);
            
            T c1 = T(this->primaryColor);
            c1.setBrightness(this->wrap(this->primaryColor.getBrightness()/255.f, .50f, .20f, .30f)*255.f);
            c1.setSaturation(this->wrap(this->primaryColor.getSaturation()/255.f, .30f, .10f, .20f)*255.f);
            this->colors.push_back(c1);
            
            T c2 = T(this->primaryColor);
            c2.setBrightness(this->wrap(this->primaryColor.getBrightness()/255.f, .20f, .20f, .60f)*255.f);
            this->colors.push_back(c2);
            
            T c3 = T(this->primaryColor);
            c3.setBrightness(fmax(.20f*255.f, this->primaryColor.getBrightness() + (255.f - this->primaryColor.getBrightness() ) * 0.2f));
            c3.setSaturation(this->wrap(this->primaryColor.getSaturation()/255.f, .30f, .10f, .30f)*255.f);
            this->colors.push_back(c3);
            
            T c4 = T(this->primaryColor);
            c4.setBrightness(this->wrap(this->primaryColor.getBrightness()/255.f, .50f, .20f, .30f)*255.f);
            this->colors.push_back(c4);
        }
        
    };

}
