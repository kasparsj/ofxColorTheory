#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
 
    class SplitComplementary : public ColorWheelScheme {
        
    public:
        SplitComplementary() : ColorWheelScheme() {
            
        }
        SplitComplementary(ofColor primaryColor) : ColorWheelScheme(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };
    
}
