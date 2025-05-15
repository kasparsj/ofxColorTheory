#pragma once

#include <vector>
#include "ColorUtil.h"

namespace ofxColorTheory {

    template<typename T>
    class ColorScheme_ {
        
    public:
        // Default constructor
        ColorScheme_() {}
        
        // Constructor with colors
        ColorScheme_(const std::vector<T>& initialColors) {
            colors = initialColors;
        }
        
        std::vector<T>& getColors() {
            return colors;
        }
        
        T& getColor(int i) {
            return colors.at(i % colors.size());
        }
        
        T& getGeneratedColor(int i) {
            if (colors.size() <= 1) {
                return colors.at(0);
            }
            return colors.at(1 + i % (colors.size() - 1));
        }
        
        virtual std::vector<T> interpolate(int num) {
            return ColorUtil::interpolate(colors, num);
        }
        
    protected:
        std::vector<T> colors;
    };
    
}
