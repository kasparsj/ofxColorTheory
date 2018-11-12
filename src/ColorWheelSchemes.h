#pragma once

#include "ColorWheelScheme.h"
#include "Analogous.h"
#include "Complementary.h"
#include "Compound.h"
#include "SplitComplementary.h"
#include "FlippedCompound.h"
#include "Monochrome.h"
#include "Tetrad.h"
#include "Triad.h"
#include "ofMath.h"

namespace ofxColorTheory {

    using namespace std;
    
    enum class ColorRule {
        RANDOM = 0, ANALOGOUS = 1, COMPLEMENTARY = 2, SPLIT_COMPLEMENTARY = 3, COMPOUND = 4, FLIPPED_COMPOUND = 5, MONOCHROME = 6, TRIAD = 7, TETRAD = 8
    };
    
    class ColorWheelSchemes {
        
    public:
        static std::vector<shared_ptr<ColorWheelScheme>> createColorSchemes() {
            std::vector<shared_ptr<ColorWheelScheme>> v;
            v.push_back(shared_ptr<ColorWheelScheme>(new Analogous()));
            v.push_back(shared_ptr<ColorWheelScheme>(new Complementary()));
            v.push_back(shared_ptr<ColorWheelScheme>(new SplitComplementary()));
            v.push_back(shared_ptr<ColorWheelScheme>(new Compound()));
            v.push_back(shared_ptr<ColorWheelScheme>(new FlippedCompound()));
            v.push_back(shared_ptr<ColorWheelScheme>(new Monochrome()));
            v.push_back(shared_ptr<ColorWheelScheme>(new Tetrad()));
            v.push_back(shared_ptr<ColorWheelScheme>(new Triad()));
            return v;
        };
        static const std::vector<shared_ptr<ColorWheelScheme>> colorSchemes;
        static const std::vector<std::string> colorSchemeNames;
        
        static shared_ptr<ColorWheelScheme> get(ColorRule rule) {
            if (rule == ColorRule::RANDOM) {
                rule = static_cast<ColorRule>((int) ofRandom(1, colorSchemes.size() + 1));
            }
            return colorSchemes[(((int) rule) - 1)];
        }
        
    };
    
}
