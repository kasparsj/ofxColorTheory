#pragma once

#include "ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class Tetrad_ : public ColorWheelScheme_<T> {
        
    public:
        Tetrad_(float angle = 90, bool alt = false) : angle(angle), alt(alt), ColorWheelScheme_<T>() {
            
        }
        Tetrad_(T primaryColor, float angle = 90, bool alt = false) : angle(angle), alt(alt), ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    private:
        float angle;
        float alt;
        
    };

    typedef Tetrad_<ofColor> Tetrad;
    
}
