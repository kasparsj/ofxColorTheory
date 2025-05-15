#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {

    template<typename T>
    class Triad_ : public ColorWheelScheme_<T> {
        
    public:
        Triad_(float angle = 90) : angle(angle), ColorWheelScheme_<T>() {
            
        }
        Triad_(T primaryColor, float angle = 90) : angle(angle), ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    private:
        float angle;
        
    };
    
}
