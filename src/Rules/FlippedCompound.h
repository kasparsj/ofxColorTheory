#pragma once

#include "../ColorWheelScheme.h"

namespace ofxColorTheory {
    
    template<typename T>
    class FlippedCompound_ : public ColorWheelScheme_<T> {
        
    public:
        FlippedCompound_() : ColorWheelScheme_<T>() {
            
        }
        FlippedCompound_(T primaryColor) : ColorWheelScheme_<T>(primaryColor) {
            generate();
        }
        
    protected:
        void generate();
        
    };
    
}
