#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
    
    class Complementary : public ColorWheelScheme {
        
    public:
        Complementary() : ColorWheelScheme() {
            
        }
        Complementary(ofColor primaryColor) : ColorWheelScheme(primaryColor) {
            generate();
        }
        std::vector<ofColor> interpolate(int steps, std::vector<ofColor> &colors);
        std::vector<ofColor> interpolate(int num) {
            return interpolate(num, colors);
        }
        
    protected:
        void generate();
        ofColor getComplement();
        ofColor adjust(ofColor color, float threshold);
        
    };
    
}
