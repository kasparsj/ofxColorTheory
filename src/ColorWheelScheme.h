#pragma once

#include "ColorScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class ColorWheelScheme_ : public ColorScheme_<T> {
        
    public:
        ColorWheelScheme_() {
            
        }
        ColorWheelScheme_(T primaryColor) : primaryColor(primaryColor) {
            
        }
        T getPrimaryColor() {
            return primaryColor;
        }
        void setPrimaryColor(T value) {
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
        T primaryColor;
        virtual void generate() = 0;
        void regenerate() {
            this->colors.clear();
            generate();
        }
        
    };

    typedef ColorWheelScheme_<ofColor> ColorWheelScheme;
    typedef ColorWheelScheme_<ofFloatColor> FloatColorWheelScheme;
    
}
