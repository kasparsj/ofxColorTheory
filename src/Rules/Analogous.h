#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class Analogous_ : public ColorWheelScheme_<T> {
        
    public:
        Analogous_(float angle = 10, float contrast = 25) : angle(angle), contrast(contrast), ColorWheelScheme_<T>() {
            
        }
        Analogous_(T primaryColor, float angle = 10, float contrast = 25) : angle(angle), contrast(contrast), ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    private:
        float angle;
        float contrast;
        
    };
    
}
