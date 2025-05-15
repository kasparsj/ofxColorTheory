#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {

    template<typename T>
    class Triad_ : public ColorWheelScheme_<T> {
        
    public:
        Triad_(float angle = 90) : angle(angle), ColorWheelScheme_<T>() {
            
        }
        Triad_(T primaryColor, float angle = 90) : angle(angle), ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate() {
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
        
    private:
        float angle;
        
    };
    
}
