#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
 
    template<typename T>
    class SplitComplementary_ : public ColorWheelScheme_<T> {
        
    public:
        SplitComplementary_() : ColorWheelScheme_<T>() {
            
        }
        SplitComplementary_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };
    
}
