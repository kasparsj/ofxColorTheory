#include "Triad.h"
#include "ColorUtil.h"

using namespace ofxColorTheory;

void Triad::generate() {
	colors.push_back(primaryColor);
	float limit = ofColor::limit();
	float bri = primaryColor.getBrightness()/limit;
	
	ofColor c1 = ColorUtil::rybRotate(primaryColor, angle);
	c1.setBrightness((bri+.1f)*limit);
	colors.push_back(c1);
	
	ofColor c2 = ColorUtil::rybRotate(primaryColor, -angle);
	c2.setBrightness((bri+.1f)*limit);
	colors.push_back(c2);
}
