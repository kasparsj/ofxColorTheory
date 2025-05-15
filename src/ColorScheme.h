#pragma once

#include "ofColor.h"
#include "ofPixels.h"
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
        
        std::vector<T> & getColors() {
            return colors;
        }
        ofPixels getPixels() {
            return ColorUtil::getPixels(colors);
        }
        T & getColor(int i) {
            return colors.at(i % colors.size());
        }
        T & getGeneratedColor(int i) {
            return colors.at(1 + i % (colors.size() - 1));
        }
        virtual std::vector<T> interpolate(int num) {
            return ColorUtil::interpolate(colors, num);
        }
        
    protected:
        std::vector<T> colors;
        
    };

    typedef ColorScheme_<ofColor> ColorScheme;
    typedef ColorScheme_<ofFloatColor> FloatColorScheme;
    
}
