#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class Analogous_ : public ColorWheelScheme_<T> {
        
    public:
        Analogous_(float angle = 10, float contrast = 25) : angle(angle), contrast(contrast), ColorWheelScheme_<T>() {
            
        }
        Analogous_(T primaryColor, float angle = 10, float contrast = 25) : angle(angle), contrast(contrast), ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        std::vector<T>& generate() {
            T newColor;
            float array[4][2] = {{1.0, 2.2}, {2.0, 1.0}, {-1.0, -0.5}, {-2.0, 1.0}};
            for (int i=0; i<4; i++) {
                float one = array[i][0];
                float two = array[i][1];

                newColor = ColorUtil::rybRotate(this->primaryColor, angle * one);
                float t = 0.44f - two * 0.1f;
                float newBri = this->primaryColor.getBrightness()/255.f - contrast/100.f * two;
                if(newBri < t) {
                    newColor.setBrightness(t * 255.f);
                } else {
                    newColor.setBrightness(newBri*255.f);
                }
                newColor.setSaturation(newColor.getSaturation()-0.05f*255.f);
                this->colors.push_back(newColor);
            }
            return this->colors;
        }
        
    private:
        float angle;
        float contrast;
        
    };
    
}
