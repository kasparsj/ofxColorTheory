#include "Complementary.h"
#include "ColorUtil.h"

using namespace ofxColorTheory;

void Complementary::generate() {
	// original
    colors.push_back(primaryColor);

	// A contrasting color: much darker or lighter than the original
    ofColor contrasting = ofColor(primaryColor);
    colors.push_back(adjust(contrasting, 0.4f));

	// A soft supporting color: lighter and less saturated
    ofColor supporting = ofColor(primaryColor);
    supporting.setBrightness(0.3f*255.f + primaryColor.getBrightness());
    supporting.setSaturation(0.1f*255.f + primaryColor.getSaturation() * 0.3f);
    colors.push_back(supporting);

    ofColor complement = getComplement();

	// A contrasting complement: very dark or very light
    ofColor contrastingComplement = ofColor(complement);
    colors.push_back(adjust(contrastingComplement, 0.3f));
	
	// The complment
	colors.push_back(complement);

	// A light supporting variant
    ofColor supportingComplement = ofColor(complement);
    supportingComplement.setBrightness(0.3f*255.f + complement.getBrightness());
    supportingComplement.setSaturation(0.1f*255.f + complement.getSaturation() * 0.25f);
    colors.push_back(supportingComplement);
}

ofColor Complementary::adjust(ofColor target, float threshold) {
	if(target.getBrightness() > threshold*255.0) {
		target.setBrightness(0.1f*255.f + target.getBrightness() * 0.25f);
	} else {
		target.setBrightness(255.f - target.getBrightness() * 0.25f);
	}
	return target;
}

ofColor Complementary::getComplement() {
	return ColorUtil::rybRotate(primaryColor, 180);
}

std::vector<ofColor> Complementary::interpolate(int steps, std::vector<ofColor> &colors) {
    std::vector<ofColor> result;
	int pri = colors.size();
	int add = steps - pri;
	int each = ceil((float) add/(pri-2));
	int pri_steps = MIN(pri, steps);
	for (int i=0; i<pri_steps; i++) {
		result.push_back(colors.at(i));
		int space = steps - result.size();
		if (space > (pri_steps - (i+1)) && i != 2) {
			for (int j=0; j<MIN(each, space); j++) {
				ofColor color = ColorUtil::lerpLch(colors.at(i), colors.at(i+1), (float) (j+1)*1/(each+1));
				result.push_back(color);
			}
		}
	}
	return result;
}
