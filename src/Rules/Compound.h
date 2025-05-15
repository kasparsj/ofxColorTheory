#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {

    template<typename T>
    class Compound_ : public ColorWheelScheme_<T> {
        
    public:
        Compound_() : ColorWheelScheme_<T>() {
            
        }
        Compound_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };
    
}
