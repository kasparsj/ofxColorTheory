#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
    
    class Tetrad : public ColorWheelScheme {
        
    public:
        Tetrad(float angle = 90, bool alt = false) : angle(angle), alt(alt), ColorWheelScheme() {
            
        }
        Tetrad(ofColor primaryColor, float angle = 90, bool alt = false) : angle(angle), alt(alt), ColorWheelScheme(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    private:
        float angle;
        float alt;
        
    };
    
}
