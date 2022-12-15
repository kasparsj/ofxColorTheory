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

    class BaseColorWheelSchemes {
        public:
            static const map<int,string> NAMES;
        
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
    };
    
    template<typename T>
    class ColorWheelSchemes_ : public BaseColorWheelSchemes {
        
    public:
        static const vector<shared_ptr<ColorWheelScheme_<T>>> SCHEMES;
        
        static vector<shared_ptr<ColorWheelScheme_<T>>> createColorSchemes() {
            vector<shared_ptr<ColorWheelScheme_<T>>> v;
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new Analogous_<T>()));
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new Complementary_<T>()));
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new SplitComplementary_<T>()));
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new Compound_<T>()));
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new FlippedCompound_<T>()));
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new Monochrome_<T>()));
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new Tetrad_<T>()));
            v.push_back(shared_ptr<ColorWheelScheme_<T>>(new Triad_<T>()));
            return v;
        };
        
        static shared_ptr<ColorWheelScheme_<T>> random() {
            return SCHEMES[(int) ofRandom(SCHEMES.size())];
        }
        
        static shared_ptr<ColorWheelScheme_<T>> get(ColorRule rule) {
            if (rule == ColorRule::RANDOM) {
                return random();
            }
            return SCHEMES[((int) rule)];
        }
        
        static shared_ptr<ColorWheelScheme_<T>> get(string name) {
            string lower = toLower(name);
            if (lower == "random") {
                return random();
            }
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

    typedef ColorWheelSchemes_<ofColor> ColorWheelSchemes;
    typedef ColorWheelSchemes_<ofFloatColor> FloatColorWheelSchemes;
    
}
