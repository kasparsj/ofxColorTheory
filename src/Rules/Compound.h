#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {

    class Compound : public ColorWheelScheme {
        
    public:
        Compound() : ColorWheelScheme() {
            
        }
        Compound(ofColor primaryColor) : ColorWheelScheme(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };
    
}
