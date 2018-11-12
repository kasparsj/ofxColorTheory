#pragma once

#include "ColorScheme.h"

namespace ofxColorTheory {
    
    class ColorWheelScheme : public ColorScheme {
        
    public:
        ColorWheelScheme() {
            
        }
        ColorWheelScheme(ofColor primaryColor) : primaryColor(primaryColor) {
            
        }
        ofColor getPrimaryColor() {
            return primaryColor;
        }
        void setPrimaryColor(ofColor value) {
            primaryColor = value;
            regenerate();
        }
        static float wrap(float x, float min, float threshold, float plus) {
            if (x - min < threshold) {
                return x + plus;
            } else {
                return x - min;
            }
        }
        
    protected:
        ofColor primaryColor;
        virtual void generate() = 0;
        void regenerate();
        
    };
    
}
