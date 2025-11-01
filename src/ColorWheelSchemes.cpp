#include "ColorWheelSchemes.h"

using namespace ofxColorTheory;

const vector<shared_ptr<ColorWheelScheme>> ColorWheelSchemes::SCHEMES = createColorSchemes();
const map<int, string> ColorWheelSchemes::NAMES = createColorSchemeNames();
