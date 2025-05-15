#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class Tetrad_ : public ColorWheelScheme_<T> {
        
    public:
        Tetrad_(float angle = 90, bool alt = false) : angle(angle), alt(alt), ColorWheelScheme_<T>() {
            
        }
        Tetrad_(T primaryColor, float angle = 90, bool alt = false) : angle(angle), alt(alt), ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate() {
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
                c1.setBrightness(bri+std::min(.2f, std::max(-.2f,.2f*multiplier)));
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
                c2.setBrightness(bri+std::min(.1f, std::max(-.1f,.1f*multiplier)));
            }
            
            this->colors.push_back(c2);
            
            T c3 = ColorUtil::rybRotate(this->primaryColor, angle * 3);
            c3.setBrightness((bri+.1f)*limit);
            this->colors.push_back(c3);
        }
        
    private:
        float angle;
        float alt;
        
    };
    
}
