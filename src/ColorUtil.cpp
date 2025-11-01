#include "ColorUtil.h"
#include <cmath>

using namespace ofxColorTheory;

const int ColorUtil::RYB_WHEEL[RYB_WHEEL_SIZE][2] = {{0, 0}, {15, 8}, {30, 17}, {45, 26}, {60, 34}, {75, 41}, {90, 48}, {105, 54}, {120, 60}, {135, 81}, {150, 103}, {165, 123}, {180, 138}, {195, 155}, {210, 171}, {225, 187}, {240, 204}, {255, 219}, {270, 234}, {285, 251}, {300, 267}, {315, 282}, {330, 298}, {345, 329}, {360, 0}};

// Helper function for degrees to radians conversion
inline float degToRad(float deg) {
    return deg * (M_PI / 180.0f);
}

// Helper function for radians to degrees conversion
inline float radToDeg(float rad) {
    return rad * (180.0f / M_PI);
}

float ColorUtil::diffLab(const Vector3f& lab1, const Vector3f& lab2) {
    /*
     * "For these and all other numerical/graphical 􏰀delta E00 values
     * reported in this article, we set the parametric weighting factors
     * to unity(i.e., k_L = k_C = k_H = 1.0)." (Page 27).
     */
    const double k_L = 1.0, k_C = 1.0, k_H = 1.0;
    const double deg360InRad = degToRad(360.0);
    const double deg180InRad = degToRad(180.0);
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
    double T = 1.0 - (0.17 * cos(barhPrime - degToRad(30.0))) +
    (0.24 * cos(2.0 * barhPrime)) +
    (0.32 * cos((3.0 * barhPrime) + degToRad(6.0))) -
    (0.20 * cos((4.0 * barhPrime) - degToRad(63.0)));
    /* Equation 16 */
    double deltaTheta = degToRad(30.0) * exp(-pow((barhPrime - degToRad(275.0)) / degToRad(25.0), 2.0));
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

Vector3f ColorUtil::XYZToLab(const Vector3f& xyz) {
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
	
	return Vector3f(( 116 * y ) - 16, 500 * ( x - y ), 200 * ( y - z ));
}

Vector3f ColorUtil::XYZToLch(const Vector3f& xyz) {
	Vector3f lab = XYZToLab(xyz);
	float c = sqrt(lab.y*lab.y + lab.z*lab.z);
	float h = atan2(lab.z, lab.y) * 180.f / M_PI;
	if (h < 0) {
		h += 360;
	}
	return Vector3f(lab.x, c, h);
}

float ColorUtil::labInv(float x) {
    float pow3 = pow(x, 3);
	if (pow3 > 0.008856) {
		return pow3;
	} else {
		return (x - (float) 16/116) / 7.787;
	}
}

Vector3f ColorUtil::LabToXYZ(const Vector3f& lab) {
	float l = (lab.x + 16.f) / 116.f;
	float a = l + lab.y / 500.f;
	float b = l - lab.z / 200.f;
	float x = wX * labInv(a);
	float y = wY * labInv(l);
	float z = wZ * labInv(b);
	return Vector3f(x, y, z);
}

Vector3f ColorUtil::LabToLch(const Vector3f& lab) {
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
	return Vector3f(l, c, h);
}

Vector3f ColorUtil::LchToLab(const Vector3f& lch) {
	//CIE-H° from 0 to 360°
	float deg2rad = M_PI / 180.f;
	float a = cos(deg2rad*lch.z) * lch.y;
	float b = sin(deg2rad*lch.z) * lch.y;
	return Vector3f(lch.x, a, b);
}

Vector3f ColorUtil::LchToXYZ(const Vector3f& lch) {
    float deg2rad = (M_PI/180.f);
	float a = lch.y * cos(lch.z*deg2rad);
	float b = lch.y * sin(lch.z*deg2rad);
	return LabToXYZ(Vector3f(lch.x, a, b));
}
