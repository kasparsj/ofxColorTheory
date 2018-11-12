#include "SplitComplementary.h"
#include "ColorUtil.h"

using namespace ofxColorTheory;

void SplitComplementary::generate() {
	colors.push_back(primaryColor);
	float limit = ofColor::limit();
	float bri = primaryColor.getBrightness()/limit;
	
	ofColor c1 = ColorUtil::rybRotate(primaryColor, 150);
	ofColor c2 = ColorUtil::rybRotate(primaryColor, 210);
	
	c1.setBrightness((bri+.1f)*limit);
	c2.setBrightness((bri+.1f)*limit);
	
	colors.push_back(c1);
	colors.push_back(c2);
}
