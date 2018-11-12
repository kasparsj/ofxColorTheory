#include "Tetrad.h"
#include "ColorUtil.h"

using namespace ofxColorTheory;

void Tetrad::generate() {
	colors.push_back(primaryColor);
	float limit = ofColor::limit();
	float bri = primaryColor.getBrightness()/limit;
	
	ofColor c1 = ColorUtil::rybRotate(primaryColor, angle);
	float multiplier;
	if(!alt)
	{
		if(bri < .5f) {
			c1.setBrightness((bri+.2f)*limit);
		} else {
			c1.setBrightness((bri-.2f)*limit);
		}
	} else {
		multiplier = (.5f-bri)/.5f;
		c1.setBrightness(bri+MIN(.2f, MAX(-.2f,.2f*multiplier)));
	}
	
	colors.push_back(c1);
	
	ofColor c2 = ColorUtil::rybRotate(primaryColor, angle * 2);
	if(!alt)
	{
		if(bri > .5f) {
			c2.setBrightness((bri+.1f)*limit);
		} else {
			c2.setBrightness((bri-.1f)*limit);
		}
	} else {
		multiplier = (.5f-bri)/.5f;
		c2.setBrightness(bri+MIN(.1f, MAX(-.1f,.1f*multiplier)));
	}
	
	colors.push_back(c2);
	
	ofColor c3 = ColorUtil::rybRotate(primaryColor, angle * 3);
	c3.setBrightness((bri+.1f)*limit);
	colors.push_back(c3);
}
