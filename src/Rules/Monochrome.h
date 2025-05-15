#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class Monochrome_ : public ColorWheelScheme_<T> {
        
    public:
        Monochrome_() : ColorWheelScheme_<T>() {
            
        }
        Monochrome_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };

}
