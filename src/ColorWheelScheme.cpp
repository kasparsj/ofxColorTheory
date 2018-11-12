#include "ColorWheelScheme.h"

using namespace ofxColorTheory;

void ColorWheelScheme::regenerate() {
    colors.clear();
    generate();
}
