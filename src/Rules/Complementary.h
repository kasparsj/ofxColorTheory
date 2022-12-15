#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class Complementary_ : public ColorWheelScheme_<T> {
        
    public:
        Complementary_() : ColorWheelScheme_<T>() {
            
        }
        Complementary_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        std::vector<T> interpolate(int steps, std::vector<T> &colors);
        std::vector<T> interpolate(int num) {
            return interpolate(num, this->colors);
        }
        
    protected:
        void generate();
        T getComplement();
        T adjust(T color, float threshold);
        
    };

    typedef Complementary_<ofColor> Complementary;
    
}
