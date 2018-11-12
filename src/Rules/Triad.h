#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {

    class Triad : public ColorWheelScheme {
        
    public:
        Triad(float angle = 90) : angle(angle), ColorWheelScheme() {
            
        }
        Triad(ofColor primaryColor, float angle = 90) : angle(angle), ColorWheelScheme(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    private:
        float angle;
        
    };
    
}
