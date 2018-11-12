#include "FlippedCompound.h"
#include "ColorUtil.h"

using namespace ofxColorTheory;

void FlippedCompound::generate() {
	colors.push_back(primaryColor);
	float limit = ofColor::limit();
	float sat = primaryColor.getSaturation()/limit;
	float bri = primaryColor.getBrightness()/limit;
	
	ofColor c1 = ColorUtil::rybRotate(primaryColor, -30);
	c1.setBrightness(wrap(bri, .25f, .6f, .25f)*limit);
	colors.push_back(c1);
	
	ofColor c2 = ColorUtil::rybRotate(primaryColor, -30);
	c2.setBrightness(wrap(bri, .4f, .1f, .4f)*limit);
	c2.setSaturation(wrap(sat, .4f, .2f, .4f)*limit);
	colors.push_back(c2);
	
	ofColor c3 = ColorUtil::rybRotate(primaryColor, -160);
	c3.setBrightness(MAX(.2f, bri)*limit);
	c3.setSaturation(wrap(sat, .25f, .1f, .25f)*limit);
	colors.push_back(c3);
	
	ofColor c4 = ColorUtil::rybRotate(primaryColor, -150);
	c4.setBrightness(wrap(bri, .3f, .6f, .3f)*limit);
	c4.setSaturation(wrap(sat, .1f, .8f, .1f)*limit);
	colors.push_back(c4);
	
	ofColor c5 = ColorUtil::rybRotate(primaryColor, -150);
	c5.setBrightness(wrap(bri, .4f, .2f, .4f)*limit);
	c5.setSaturation(wrap(sat, .1f, .8f, .1f)*limit);
	colors.push_back(c5);
}
