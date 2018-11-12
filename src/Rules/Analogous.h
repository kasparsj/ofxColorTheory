#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
    
    class Analogous : public ColorWheelScheme {
        
    public:
        Analogous(float angle = 10, float contrast = 25) : angle(angle), contrast(contrast), ColorWheelScheme() {
            
        }
        Analogous(ofColor primaryColor, float angle = 10, float contrast = 25) : angle(angle), contrast(contrast), ColorWheelScheme(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    private:
        float angle;
        float contrast;
        
    };
    
}
