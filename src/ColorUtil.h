#pragma once

#include <vector>
#include <cmath>

#define RYB_WHEEL_SIZE 25

namespace ofxColorTheory {

    // Vector3f class to replace ofVec3f
    struct Vector3f {
        float x, y, z;
        
        Vector3f() : x(0), y(0), z(0) {}
        Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    };

    // Helper function to clamp a value between min and max
    inline float clamp(float value, float min_val, float max_val) {
        return std::max(min_val, std::min(max_val, value));
    }

    // Convert XYZ to RGB color space
    // This function creates RGB values in 0.0-1.0 range from XYZ values
    inline void xyzToRgb(const Vector3f& xyz, float& r, float& g, float& b) {
        // Normalize XYZ values
        float x = clamp(xyz.x, 0.0f, 95.047f)/100.0f;
        float y = xyz.y/100.0f;
        float z = xyz.z/100.0f;
        
        // Apply XYZ to RGB matrix transformation
        r = x * 3.2406f + y * -1.5372f + z * -0.4986f;
        g = x * -0.9689f + y * 1.8758f + z * 0.0415f;
        b = x * 0.0557f + y * -0.2040f + z * 1.0570f;
        
        // Apply gamma correction
        if (r > 0.0031308f) {
            r = 1.055f * pow(r, 1.0f / 2.4f) - 0.055f;
        } else {
            r = 12.92f * r;
        }
        
        if (g > 0.0031308f) {
            g = 1.055f * pow(g, 1.0f / 2.4f) - 0.055f;
        } else {
            g = 12.92f * g;
        }
        
        if (b > 0.0031308f) {
            b = 1.055f * pow(b, 1.0f / 2.4f) - 0.055f;
        } else {
            b = 12.92f * b;
        }
        
        // Ensure values are in valid range 0.0-1.0
        r = clamp(r, 0.0f, 1.0f);
        g = clamp(g, 0.0f, 1.0f);
        b = clamp(b, 0.0f, 1.0f);
    }

    class ColorUtil {
        
    public:
        template<typename T>
        static std::vector<T> interpolate(const std::vector<T>& colors, int steps) {
            std::vector<T> result;
            int pri = colors.size();
            int add = steps - pri;
            int each = ceil((float) add/(pri-1));
            int pri_steps = std::min(pri, steps);
            for (int i=0; i<pri_steps; i++) {
                result.push_back(colors.at(i));
                int space = steps - result.size();
                if (space > (pri_steps - (i+1))) {
                    for (int j=0; j<std::min(each, space); j++) {
                        T color = lerpLch(colors.at(i), colors.at(i+1), (float) (j+1)*1/(each+1));
                        result.push_back(color);
                    }
                }
            }
            return result;
        }

        // Template function for rotating a color in RYB color space
        template<typename T>
        static T rybRotate(const T& color, float angle) {
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
        
        // Template methods for color operations
        template<typename T>
        static float diffRGB(const T& c1, const T& c2) {
            int r = c1.r - c2.r;
            int g = c1.g - c2.g;
            int b = c1.b - c2.b;
            return sqrt(r*r + g*g + b*b);
        }
        
        static float diffLab(const Vector3f& lab1, const Vector3f& lab2);
        
        template<typename T>
        static T lerpRGB(const T& c1, const T& c2, float amt) {
            return c1.lerp(c2, amt);
        }
        
        template<typename T>
        static T lerpHSB(const T& c1, const T& c2, float amt) {
            float limit = T::limit();
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
            return T::fromHsb(hue, sat, bri);
        }
        
        template<typename T>
        static T lerpLch(const T& c1, const T& c2, float amt) {
            // Get LCH values for both colors
            Vector3f lch1 = toLch<T>(c1);
            Vector3f lch2 = toLch<T>(c2);
            float invAmt = 1.f - amt;
            
            // Linear interpolation for L and C components
            float l = invAmt * lch1.x + lch2.x * amt;
            float c = invAmt * lch1.y + lch2.y * amt;
            
            // Special handling for hue component to ensure shortest path
            float h1 = lch1.z;
            float h2 = lch2.z;
            float dh12 = (h1 >= h2) ? h1 - h2 : 360.f - h2 + h1;
            float dh21 = (h2 >= h1) ? h2 - h1 : 360.f - h1 + h2;
            float h = (dh21 < dh12) ? h1 + dh21 * amt : h1 - dh12 * amt;
            
            // Normalize hue to 0-360 range
            if (h < 0.0) {
                h += 360.f;
            }
            else if (h > 360.f) {
                h -= 360.f;
            }
            
            // Convert back to original color space
            return fromLch<T>(Vector3f(l, c, h));
        }
        
        template<typename T>
        static T lerpColors(const T& c1, const T& c2, float p) {
            // Default to LCH interpolation 
            return lerpLch(c1, c2, p);
        }
        
        template<typename T>
        static T fromXYZ(const Vector3f& xyz) {
            float r, g, b;
            xyzToRgb(xyz, r, g, b);
            
            // Convert to target color type using appropriate scaling
            float limit = T::limit();
            return T(r * limit, g * limit, b * limit);
        }
        
        template<typename T>
        static T fromLab(const Vector3f& lab) {
            // Convert Lab to XYZ, then XYZ to target color type
            Vector3f xyz = LabToXYZ(lab);
            return fromXYZ<T>(xyz);
        }
        
        template<typename T>
        static T fromLch(const Vector3f& lch) {
            // Convert LCH to XYZ, then XYZ to target color type
            Vector3f xyz = LchToXYZ(lch);
            return fromXYZ<T>(xyz);
        }
        
        template<typename T>
        static Vector3f toXYZ(const T& color) {
            float limit = T::limit();
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
            return Vector3f(x, y, z);
        }
        
        template<typename T>
        static Vector3f toLab(const T& color) {
            // Convert color to XYZ, then XYZ to Lab
            Vector3f xyz = toXYZ<T>(color);
            return XYZToLab(xyz);
        }
        
        template<typename T>
        static Vector3f toLch(const T& color) {
            // Convert color to XYZ, then XYZ to LCH
            Vector3f xyz = toXYZ<T>(color);
            return XYZToLch(xyz);
        }
        
        static Vector3f XYZToRGB(const Vector3f& xyz);
        static Vector3f XYZToLab(const Vector3f& xyz);
        static Vector3f XYZToLch(const Vector3f& xyz);
        static Vector3f LabToLch(const Vector3f& lab);
        static Vector3f LabToXYZ(const Vector3f& lab);
        static Vector3f LchToLab(const Vector3f& lch);
        static Vector3f LchToXYZ(const Vector3f& lch);
        
    private:
        static constexpr float wX = 95.047;
        static constexpr float wY = 100.000;
        static constexpr float wZ = 108.883;
        static float labInv(float x);
        static const int RYB_WHEEL[RYB_WHEEL_SIZE][2];
    };
}
