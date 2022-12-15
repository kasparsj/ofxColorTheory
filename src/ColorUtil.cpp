#include "ColorUtil.h"
#include "ofMath.h"

using namespace ofxColorTheory;

const int ColorUtil::RYB_WHEEL[RYB_WHEEL_SIZE][2] = {{0, 0}, {15, 8}, {30, 17}, {45, 26}, {60, 34}, {75, 41}, {90, 48}, {105, 54}, {120, 60}, {135, 81}, {150, 103}, {165, 123}, {180, 138}, {195, 155}, {210, 171}, {225, 187}, {240, 204}, {255, 219}, {270, 234}, {285, 251}, {300, 267}, {315, 282}, {330, 298}, {345, 329}, {360, 0}};

ofColor ColorUtil::rybRotate(ofColor color, float angle) {
    float hue = color.getHueAngle();
    float a = 0;
    for (int i=0; i<(RYB_WHEEL_SIZE-1); i++) {
        int x0 = RYB_WHEEL[i][0];
        int y0 = RYB_WHEEL[i][1];
        
        int x1 = RYB_WHEEL[i + 1][0];
        int y1 = RYB_WHEEL[i + 1][1];
        if(y1 < y0)  y1 += 360;
        if(y0 <= hue && hue <= y1) {
            a = x0 + (x1 - x0) * (hue - y0) / (y1 - y0);
            break;
        }
    }
    
    a = (a + fmod(angle, 360));
    if (a < 0)  a = 360 + a;
    if (a > 360)  a = a - 360;
    a = fmod(a, 360);
    
    float newHue;
    for (int k=0; k<(RYB_WHEEL_SIZE-1); k++) {
        int xx0 = RYB_WHEEL[k][0];
        int yy0 = RYB_WHEEL[k][1];
        
        int xx1 = RYB_WHEEL[k + 1][0];
        int yy1 = RYB_WHEEL[k + 1][1];
        if (yy1 < yy0) yy1 += 360;
        if (xx0 <= a && a <= xx1) {
            newHue = yy0 + (yy1 - yy0) * (a - xx0) / (xx1 - xx0);
            break;
        }
    }
    
    color.setHue(newHue/360.f*255.0);
    return color;
}

template<typename T>
std::vector<T> ColorUtil::interpolate(const std::vector<T> & colors, int steps) {
    std::vector<T> result;
    int pri = colors.size();
    int add = steps - pri;
    int each = ceil((float) add/(pri-1));
    int pri_steps = MIN(pri, steps);
    for (int i=0; i<pri_steps; i++) {
        result.push_back(colors.at(i));
        int space = steps - result.size();
        if (space > (pri_steps - (i+1))) {
            for (int j=0; j<MIN(each, space); j++) {
                T color = ColorUtil::lerpLch(colors.at(i), colors.at(i+1), (float) (j+1)*1/(each+1));
                result.push_back(color);
            }
        }
    }
    return result;
}

template std::vector<ofColor> ColorUtil::interpolate<ofColor>(const std::vector<ofColor> &colors, int steps);
template std::vector<ofFloatColor> ColorUtil::interpolate<ofFloatColor>(const std::vector<ofFloatColor> &colors, int steps);

ofPixels ColorUtil::getPixels(const std::vector<ofColor> &colors) {
    ofPixels pixels;
    pixels.allocate(colors.size(), 1, OF_PIXELS_RGB);
    for (int i=0; i<colors.size(); i++) {
        pixels.setColor(pixels.getPixelIndex(i, 0), colors[i]);
    }
    return pixels;
}

std::vector<ofColor> ColorUtil::getColors(const ofPixels & pixels) {
    std::vector<ofColor> result;
    for (int i=0; i<pixels.getHeight(); i++) {
        for (int j=0; j<pixels.getWidth(); j++) {
            result.push_back(pixels.getColor(j, i));
        }
    }
    return result;
}

float ColorUtil::diffRGB(ofColor c1, ofColor c2) {
    int r = c1.r - c2.r;
    int g = c1.g - c2.g;
    int b = c1.b - c2.b;
    return sqrt(r*r + g*g + b*b);
}

float ColorUtil::diffLab(ofVec3f lab1, ofVec3f lab2) {
    /*
     * "For these and all other numerical/graphical 􏰀delta E00 values
     * reported in this article, we set the parametric weighting factors
     * to unity(i.e., k_L = k_C = k_H = 1.0)." (Page 27).
     */
    const double k_L = 1.0, k_C = 1.0, k_H = 1.0;
    const double deg360InRad = ofDegToRad(360.0);
    const double deg180InRad = ofDegToRad(180.0);
    const double pow25To7 = 6103515625.0; /* pow(25, 7) */
    
    /*
     * Step 1
     */
    /* Equation 2 */
    double C1 = sqrt((lab1.y * lab1.y) + (lab1.z * lab1.z));
    double C2 = sqrt((lab2.y * lab2.y) + (lab2.z * lab2.z));
    /* Equation 3 */
    double barC = (C1 + C2) / 2.0;
    /* Equation 4 */
    double G = 0.5 * (1 - sqrt(pow(barC, 7) / (pow(barC, 7) + pow25To7)));
    /* Equation 5 */
    double a1Prime = (1.0 + G) * lab1.y;
    double a2Prime = (1.0 + G) * lab2.y;
    /* Equation 6 */
    double CPrime1 = sqrt((a1Prime * a1Prime) + (lab1.z * lab1.z));
    double CPrime2 = sqrt((a2Prime * a2Prime) + (lab2.z * lab2.z));
    /* Equation 7 */
    double hPrime1;
    if (lab1.z == 0 && a1Prime == 0)
        hPrime1 = 0.0;
    else {
        hPrime1 = atan2(lab1.z, a1Prime);
        /*
         * This must be converted to a hue angle in degrees between 0
         * and 360 by addition of 2􏰏 to negative hue angles.
         */
        if (hPrime1 < 0)
            hPrime1 += deg360InRad;
    }
    double hPrime2;
    if (lab2.z == 0 && a2Prime == 0)
        hPrime2 = 0.0;
    else {
        hPrime2 = atan2(lab2.z, a2Prime);
        /*
         * This must be converted to a hue angle in degrees between 0
         * and 360 by addition of 2􏰏 to negative hue angles.
         */
        if (hPrime2 < 0)
            hPrime2 += deg360InRad;
    }
    
    /*
     * Step 2
     */
    /* Equation 8 */
    double deltaLPrime = lab2.x - lab1.x;
    /* Equation 9 */
    double deltaCPrime = CPrime2 - CPrime1;
    /* Equation 10 */
    double deltahPrime;
    double CPrimeProduct = CPrime1 * CPrime2;
    if (CPrimeProduct == 0)
        deltahPrime = 0;
    else {
        /* Avoid the fabs() call */
        deltahPrime = hPrime2 - hPrime1;
        if (deltahPrime < -deg180InRad)
            deltahPrime += deg360InRad;
        else if (deltahPrime > deg180InRad)
            deltahPrime -= deg360InRad;
    }
    /* Equation 11 */
    double deltaHPrime = 2.0 * sqrt(CPrimeProduct) *
    sin(deltahPrime / 2.0);
    
    /*
     * Step 3
     */
    /* Equation 12 */
    double barLPrime = (lab1.x + lab2.x) / 2.0;
    /* Equation 13 */
    double barCPrime = (CPrime1 + CPrime2) / 2.0;
    /* Equation 14 */
    double barhPrime, hPrimeSum = hPrime1 + hPrime2;
    if (CPrime1 * CPrime2 == 0) {
        barhPrime = hPrimeSum;
    } else {
        if (fabs(hPrime1 - hPrime2) <= deg180InRad)
            barhPrime = hPrimeSum / 2.0;
        else {
            if (hPrimeSum < deg360InRad)
                barhPrime = (hPrimeSum + deg360InRad) / 2.0;
            else
                barhPrime = (hPrimeSum - deg360InRad) / 2.0;
        }
    }
    /* Equation 15 */
    double T = 1.0 - (0.17 * cos(barhPrime - ofDegToRad(30.0))) +
    (0.24 * cos(2.0 * barhPrime)) +
    (0.32 * cos((3.0 * barhPrime) + ofDegToRad(6.0))) -
    (0.20 * cos((4.0 * barhPrime) - ofDegToRad(63.0)));
    /* Equation 16 */
    double deltaTheta = ofDegToRad(30.0) * exp(-pow((barhPrime - ofDegToRad(275.0)) / ofDegToRad(25.0), 2.0));
    /* Equation 17 */
    double R_C = 2.0 * sqrt(pow(barCPrime, 7.0) /
                            (pow(barCPrime, 7.0) + pow25To7));
    /* Equation 18 */
    double S_L = 1 + ((0.015 * pow(barLPrime - 50.0, 2.0)) /
                      sqrt(20 + pow(barLPrime - 50.0, 2.0)));
    /* Equation 19 */
    double S_C = 1 + (0.045 * barCPrime);
    /* Equation 20 */
    double S_H = 1 + (0.015 * barCPrime * T);
    /* Equation 21 */
    double R_T = (-sin(2.0 * deltaTheta)) * R_C;
    
    /* Equation 22 */
    double deltaE = sqrt(
                         pow(deltaLPrime / (k_L * S_L), 2.0) +
                         pow(deltaCPrime / (k_C * S_C), 2.0) +
                         pow(deltaHPrime / (k_H * S_H), 2.0) +
                         (R_T * (deltaCPrime / (k_C * S_C)) * (deltaHPrime / (k_H * S_H))));
    
    return (deltaE);
}

ofColor ColorUtil::lerpRGB(ofColor c1, ofColor c2, float amt) {
	return c1.lerp(c2, amt);
}

ofColor ColorUtil::lerpHSB(ofColor c1, ofColor c2, float amt) {
	float limit = ofColor::limit();
	float h1 = c1.getHue();
	float h2 = c2.getHue();
	float dh12 = (h1 >= h2) ? h1 - h2 : limit - h2 + h1;
	float dh21 = (h2 >= h1) ? h2 - h1 : limit - h1 + h2;
	float hue = (dh21 < dh12) ? h1 + dh21 * amt : h1 - dh12 * amt;
	if (hue < 0.0) {
		hue += limit;
	}
	else if (hue > limit) {
		hue -= limit;
	}
	float invAmt = 1.f - amt;
	float sat = invAmt * c1.getSaturation() + c2.getSaturation() * amt;
	float bri = invAmt * c1.getBrightness() + c2.getBrightness() * amt;
	return ofColor::fromHsb(hue, sat, bri);
}

ofColor ColorUtil::lerpLch(ofColor c1, ofColor c2, float amt) {
	ofVec3f lch1 = toLch(c1);
	ofVec3f lch2 = toLch(c2);
    float invAmt = 1.f - amt;
    float l = invAmt * lch1.x + lch2.x * amt;
    float c = invAmt * lch1.y + lch2.y * amt;
    float h1 = lch1.z;
    float h2 = lch2.z;
    float dh12 = (h1 >= h2) ? h1 - h2 : 360.f - h2 + h1;
    float dh21 = (h2 >= h1) ? h2 - h1 : 360.f - h1 + h2;
    float h = (dh21 < dh12) ? h1 + dh21 * amt : h1 - dh12 * amt;
    if (h < 0.0) {
        h += 360.f;
    }
    else if (h > 360.f) {
        h -= 360.f;
    }
    return fromLch(ofVec3f(l, c, h));
//	float l = lch1.x;
//	float c = lch1.y;
//	float h = lch1.z;
//	float dl = lch2.x - l;
//	float dc = lch2.y - c;
//	float dh = lch2.z - h;
//	dh > 180 ? dh -= 360.f : dh < -180 && (dh += 360.f);
//	return fromLch(ofVec3f(l + dl * amt, c + dc * amt, h + dh * amt));
}

ofColor ColorUtil::fromXYZ(ofVec3f xyz) {
	float x = ofClamp(xyz.x, 0, 95.047)/100.f;
	float y = xyz.y/100.f;
	float z = xyz.z/100.f;
	
	float r = x * 3.2406 + y * -1.5372 + z * -0.4986;
	float g = x * -0.9689 + y * 1.8758 + z * 0.0415;
	float b = x * 0.0557 + y * -0.2040 + z * 1.0570;
	
	if (r > 0.0031308) {
		r = 1.055 * pow( r , (float) 1 / 2.4f) - 0.055;
	} else {
		r = 12.92 * r;
	}
	if (g > 0.0031308) {
		g = 1.055 * pow( g , (float) 1 / 2.4f) - 0.055;
	} else {
		g = 12.92 * g;
	}
	if (b > 0.0031308) {
		b = 1.055 * pow( b , (float) 1 / 2.4f) - 0.055;
	} else {
		b = 12.92 * b;
	}

	float limit = ofColor::limit();
	return ofColor(ofClamp(r*limit, 0, 255), ofClamp(g*limit, 0, 255), ofClamp(b*limit, 0, 255));
}

ofColor ColorUtil::fromLab(ofVec3f lab) {
	return fromXYZ(LabToXYZ(lab));
}

ofColor ColorUtil::fromLch(ofVec3f lch) {
	return fromXYZ(LchToXYZ(lch));
}

ofVec3f ColorUtil::toXYZ(ofColor color) {
	float limit = ofColor::limit();
	float r = color.r/limit;
	float g = color.g/limit;
	float b = color.b/limit;
	
	if (r > 0.04045) {
		r = pow((r + 0.055) / 1.055, 2.4);
	} else {
		r = r / 12.92;
	}
	if ( g > 0.04045){
		g = pow((g + 0.055) / 1.055, 2.4);
	} else {
		g = g / 12.92;
	}
	if (b > 0.04045){
		b = pow((b + 0.055) / 1.055, 2.4);
	} else {
		b = b / 12.92;
	}
	r *= 100;
	g *= 100;
	b *= 100;
	
	//Observer. = 2°, Illuminant = D65
	float x = r * 0.4124 + g * 0.3576 + b * 0.1805;
	float y = r * 0.2126 + g * 0.7152 + b * 0.0722;
	float z = r * 0.0193 + g * 0.1192 + b * 0.9505;
	return ofVec3f(x, y, z);
}

ofVec3f ColorUtil::toLab(ofColor color) {
	return XYZToLab(toXYZ(color));
}

ofVec3f ColorUtil::toLch(ofColor color) {
	return XYZToLch(toXYZ(color));
}

ofVec3f ColorUtil::XYZToLab(ofVec3f xyz) {
	float x = xyz.x / 95.047;   // Observer= 2°, Illuminant= D65
	float y = xyz.y / 100.000;
	float z = xyz.z / 108.883;

	if (x > 0.008856) {
        x = pow(x , (float) 1/3);
    } else {
        x = ( 7.787 * x ) + (float) 16/116;
    }
	if (y > 0.008856) {
        y = pow(y , (float) 1/3);
    } else {
        y = ( 7.787 * y ) + (float) 16/116;
    }
	if (z > 0.008856) {
        z = pow(z , (float) 1/3);
    } else {
        z = ( 7.787 * z ) + (float) 16/116;
    }
	
	return ofVec3f(( 116 * y ) - 16, 500 * ( x - y ), 200 * ( y - z ));
}

ofVec3f ColorUtil::XYZToLch(ofVec3f xyz) {
	ofVec3f lab = XYZToLab(xyz);
	float c = sqrt(lab.y*lab.y + lab.z*lab.z);
	float h = atan2(lab.z, lab.y) * 180.f / M_PI;
	if (h < 0) {
		h += 360;
	}
	return ofVec3f(lab.x, c, h);
}

float ColorUtil::labInv(float x) {
    float pow3 = pow(x, 3);
	if (pow3 > 0.008856) {
		return pow3;
	} else {
		return (x - (float) 16/116) / 7.787;
	}
}

ofVec3f ColorUtil::LabToXYZ(ofVec3f lab) {
	float l = (lab.x + 16.f) / 116.f;
	float a = l + lab.y / 500.f;
	float b = l - lab.z / 200.f;
	float x = wX * labInv(a);
	float y = wY * labInv(l);
	float z = wZ * labInv(b);
	return ofVec3f(x, y, z);
}

ofVec3f ColorUtil::LabToLch(ofVec3f lab) {
	float l = lab.x;
	float a = lab.y;
	float b = lab.z;
	float c = sqrt(a * a + b * b);
	float h = atan2(b, a) / M_PI * 180.f;
	//	if h > 0 {
	//		h = (h / math.Pi) * 180.0
	//	} else {
	//		h = 360.0 - (math.Abs(h)/math.Pi)*180.0
	//	}
	return ofVec3f(l, c, h);
}

ofVec3f ColorUtil::LchToLab(ofVec3f lch) {
	//CIE-H° from 0 to 360°
	float deg2rad = M_PI / 180.f;
	float a = cos(deg2rad*lch.z) * lch.y;
	float b = sin(deg2rad*lch.z) * lch.y;
	return ofVec3f(lch.x, a, b);
}

ofVec3f ColorUtil::LchToXYZ(ofVec3f lch) {
    float deg2rad = (M_PI/180.f);
	float a = lch.y * cos(lch.z*deg2rad);
	float b = lch.y * sin(lch.z*deg2rad);
	return LabToXYZ(ofVec3f(lch.x, a, b));
}
