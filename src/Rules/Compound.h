#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {

    template<typename T>
    class Compound_ : public ColorWheelScheme_<T> {
        
    public:
        Compound_() : ColorWheelScheme_<T>() {
            
        }
        Compound_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate() {
            this->colors.push_back(this->primaryColor);
            
            T c1 = ColorUtil::rybRotate(this->primaryColor, 30);
            c1.setBrightness(this->wrap(this->primaryColor.getBrightness()/255.f, .25f, .60f, .25f)*255.f);
            this->colors.push_back(c1);
            
            T c2 = ColorUtil::rybRotate(this->primaryColor, 30);
            c2.setBrightness(this->wrap(this->primaryColor.getBrightness()/255.f, .40f, .10f, .40f)*255.f);
            c2.setSaturation(this->wrap(this->primaryColor.getSaturation()/255.f, .40f, .20f, .40f)*255.f);
            this->colors.push_back(c2);
            
            T c3 = ColorUtil::rybRotate(this->primaryColor, 160);
            c3.setBrightness(fmax(.20f, this->primaryColor.getBrightness()/255.f)*255.f);
            c3.setSaturation(this->wrap(this->primaryColor.getSaturation()/255.f, .25f, .10f, .25f)*255.f);
            this->colors.push_back(c3);
            
            T c4 = ColorUtil::rybRotate(this->primaryColor, 150);
            c4.setBrightness(this->wrap(this->primaryColor.getBrightness()/255.f, .30f, .60f, .30f)*255.f);
            c4.setSaturation(this->wrap(this->primaryColor.getSaturation()/255.f, .10f, .80f, .10f)*255.f);
            this->colors.push_back(c4);
            
            T c5 = ColorUtil::rybRotate(this->primaryColor, 150);
            c5.setBrightness(this->wrap(this->primaryColor.getBrightness()/255.f, .40f, .20f, .40f)*255.f);
            c5.setSaturation(this->wrap(this->primaryColor.getSaturation()/255.f, .10f, .80f, .10f)*255.f);
            this->colors.push_back(c5);
        }
        
    };
    
}
