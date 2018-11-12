#pragma once

#include "ofVec3f.h"
#include "ofColor.h"
#include "ofPixels.h"

#define RYB_WHEEL_SIZE 25

namespace ofxColorTheory {

    class ColorUtil {
        
    public:
        static std::vector<ofColor> interpolate(const std::vector<ofColor> & colors, int steps);
        static ofColor rybRotate(ofColor color, float angle);
        static ofPixels getPixels(const std::vector<ofColor> & colors);
        static std::vector<ofColor> getColors(const ofPixels & pixels);
        static float diffRGB(ofColor c1, ofColor c2);
        static float diffLab(ofVec3f lab1, ofVec3f lab2);
        static ofColor lerpRGB(ofColor c1, ofColor c2, float p);
        static ofColor lerpHSB(ofColor c1, ofColor c2, float p);
        static ofColor lerpLch(ofColor c1, ofColor c2, float p);
        static ofColor fromXYZ(ofVec3f);
        static ofColor fromLab(ofVec3f);
        static ofColor fromLch(ofVec3f);
        static ofVec3f toXYZ(ofColor color);
        static ofVec3f toLab(ofColor color);
        static ofVec3f toLch(ofColor color);
        static ofVec3f XYZToRGB(ofVec3f xyz);
        static ofVec3f XYZToLab(ofVec3f xyz);
        static ofVec3f XYZToLch(ofVec3f xyz);
        static ofVec3f LabToLch(ofVec3f lab);
        static ofVec3f LabToXYZ(ofVec3f lab);
        static ofVec3f LchToLab(ofVec3f lch);
        static ofVec3f LchToXYZ(ofVec3f lch);
        
    private:
        static constexpr float wX = 95.047;
        static constexpr float wY = 100.000;
        static constexpr float wZ = 108.883;
        static float labInv(float x);
        static const int RYB_WHEEL[RYB_WHEEL_SIZE][2];
        
    };

    
}
