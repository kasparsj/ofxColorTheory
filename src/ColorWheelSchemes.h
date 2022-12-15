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
#include <map>

namespace ofxColorTheory {

    using namespace std;
    
    enum class ColorRule {
        RANDOM = -1, ANALOGOUS = 0, COMPLEMENTARY = 1, SPLIT_COMPLEMENTARY = 2, COMPOUND = 3, FLIPPED_COMPOUND = 4, MONOCHROME = 5, TRIAD = 6, TETRAD = 7
    };
    
    class ColorWheelSchemes {
        
    public:
        static const vector<shared_ptr<ColorWheelScheme>> SCHEMES;
        static const map<int,string> NAMES;
        
        static vector<shared_ptr<ColorWheelScheme>> createColorSchemes() {
            vector<shared_ptr<ColorWheelScheme>> v;
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
        
        static map<int, string> createColorSchemeNames() {
            map<int, string> names;
            names[(int) ColorRule::ANALOGOUS] = "Analogous";
            names[(int) ColorRule::COMPLEMENTARY] = "Complementary";
            names[(int) ColorRule::SPLIT_COMPLEMENTARY] = "SplitComplementary";
            names[(int) ColorRule::COMPOUND] = "Compound";
            names[(int) ColorRule::FLIPPED_COMPOUND] = "FlippedCompound";
            names[(int) ColorRule::MONOCHROME] = "Monochrome";
            names[(int) ColorRule::TETRAD] = "Tetrad";
            names[(int) ColorRule::TRIAD] = "Triad";
            return names;
        };
        
        static shared_ptr<ColorWheelScheme> get(ColorRule rule) {
            if (rule == ColorRule::RANDOM) {
                rule = static_cast<ColorRule>((int) ofRandom(SCHEMES.size()));
            }
            return SCHEMES[((int) rule)];
        }
        
        static shared_ptr<ColorWheelScheme> get(string name) {
            string lower = toLower(name);
            for (map<int, string>::const_iterator it=NAMES.begin(); it!=NAMES.end(); ++it) {
                string l = toLower(it->second);
                if (lower == l) {
                    return SCHEMES[it->first];
                }
            }
            return NULL;
        }
        
    private:
        static string toLower(string str) {
            transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
            return str;
        }
        
    };
    
}
