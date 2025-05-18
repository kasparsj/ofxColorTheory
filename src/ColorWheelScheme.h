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
        }
        static float wrap(float x, float min, float threshold, float plus) {
            if (x - min < threshold) {
                return x + plus;
            } else {
                return x - min;
            }
        }
        virtual std::vector<T>& generate() = 0;
        std::vector<T>& regenerate() {
            this->colors.clear();
            return generate();
        }
        
    protected:
        T primaryColor;
        
    };
    
}
