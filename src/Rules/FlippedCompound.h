#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
    
    class FlippedCompound : public ColorWheelScheme {
        
    public:
        FlippedCompound() : ColorWheelScheme() {
            
        }
        FlippedCompound(ofColor primaryColor) : ColorWheelScheme(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };
    
}
