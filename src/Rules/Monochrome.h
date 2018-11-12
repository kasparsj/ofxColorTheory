#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
    
    class Monochrome : public ColorWheelScheme {
        
    public:
        Monochrome() : ColorWheelScheme() {
            
        }
        Monochrome(ofColor primaryColor) : ColorWheelScheme(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };
    
}
