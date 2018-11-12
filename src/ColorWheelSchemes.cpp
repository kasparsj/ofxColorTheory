#include "ColorWheelSchemes.h"

using namespace ofxColorTheory;

const std::vector<shared_ptr<ColorWheelScheme>> ColorWheelSchemes::colorSchemes = createColorSchemes();
const std::vector<std::string> ColorWheelSchemes::colorSchemeNames = {"Analogous", "Complementary", "SplitComplementary", "Compound", "FlippedCompound", "Monochrome", "Tetrad", "Triad"};
