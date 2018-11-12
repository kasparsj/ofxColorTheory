#pragma once

#include "ofColor.h"
#include "ofPixels.h"
#include "ColorUtil.h"

namespace ofxColorTheory {

    class ColorScheme {
        
    public:
        std::vector<ofColor> & getColors() {
            return colors;
        }
        ofPixels getPixels() {
            return ColorUtil::getPixels(colors);
        }
        ofColor & getColor(int i) {
            return colors.at(i % colors.size());
        }
        ofColor & getGeneratedColor(int i) {
            return colors.at(1 + i % (colors.size() - 1));
        }
        virtual std::vector<ofColor> interpolate(int num) {
            return ColorUtil::interpolate(colors, num);
        }
        
    protected:
        std::vector<ofColor> colors;
        
    };
    
}
