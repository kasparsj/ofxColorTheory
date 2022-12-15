#include "ColorWheelSchemes.h"

namespace ofxColorTheory {

const map<int, string> BaseColorWheelSchemes::NAMES = BaseColorWheelSchemes::createColorSchemeNames();

template<>
const vector<shared_ptr<ColorWheelScheme_<ofColor>>> ColorWheelSchemes_<ofColor>::SCHEMES = ColorWheelSchemes_<ofColor>::createColorSchemes();

template<>
const vector<shared_ptr<ColorWheelScheme_<ofFloatColor>>> ColorWheelSchemes_<ofFloatColor>::SCHEMES = ColorWheelSchemes_<ofFloatColor>::createColorSchemes();

template class ColorWheelSchemes_<ofColor>;
template class ColorWheelSchemes_<ofFloatColor>;

}
