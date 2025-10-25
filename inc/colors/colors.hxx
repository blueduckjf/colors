#pragma once
#include <stdint.h>
#include "libfixmath/fix16.hpp"

namespace Colors
{
    class HSV;

    class RGB
    {
        public:
            uint8_t r;
            uint8_t g;
            uint8_t b;

            constexpr RGB(uint8_t red, uint8_t green, uint8_t blue)
                : r(red), g(green), b(blue) { }

            RGB(const RGB&) = default;
            RGB(RGB&&) = default;
            RGB(const HSV& hsv);
            inline RGB(HSV&& hsv) : RGB(static_cast<const HSV&>(hsv)) { }
            RGB& operator=(const RGB&) = default;
            RGB& operator=(RGB&&) = default;
            RGB& operator=(const HSV& hsv);
            inline RGB& operator=(HSV&& hsv) { return operator=(static_cast<const HSV&>(hsv)); }

            static HSV ToHSV(const RGB& rgb);
            HSV ToHSV() const;
            operator HSV() const;

            static constexpr RGB GammaCorrection(const RGB& rgb)
            {
                constexpr uint8_t GammaCorrectionTable[] =
                {
                        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
                        2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
                        5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
                        10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
                        17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
                        25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
                        37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
                        51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
                        69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
                        90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
                        115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
                        144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
                        177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
                        215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
                };

                return RGB
                (
                    GammaCorrectionTable[rgb.r],
                    GammaCorrectionTable[rgb.g],
                    GammaCorrectionTable[rgb.b]
                );
            }

            inline RGB GammaCorrection() const { return GammaCorrection(*this); }
    };

    class HSV
    {
        friend class RGB;

        private:
            static void FromRgb(const RGB& rgb, Fix16& hue, Fix16& sat, Fix16& val);

        public:
            Fix16 h;
            Fix16 s;
            Fix16 v;

            inline HSV(Fix16 hue, Fix16 saturation, Fix16 value)
                : h(hue), s(saturation), v(value)
            { } 

            HSV(const HSV&) = default;
            HSV(HSV&&) = default;
            HSV(const RGB& rgb);
            inline HSV(RGB&& rgb) : HSV(static_cast<const RGB&>(rgb)) { } 
            HSV& operator=(const HSV&) = default;
            HSV& operator=(HSV&&) = default;
            HSV& operator=(const RGB& rgb);
            inline HSV& operator=(RGB&& rgb) { return operator=(static_cast<const RGB&>(rgb)); } 

            static RGB ToRGB(const HSV& hsv);
            inline RGB ToRGB() const { return ToRGB(*this); }
            inline operator RGB() const { return ToRGB(); }

            static HSV GammaCorrection(const HSV& hsv);
            inline HSV GammaCorrection() const { return GammaCorrection(*this); }
    };

    namespace Palette
    {
        constexpr RGB Red      { 0xFF, 0x00, 0x00 };
        constexpr RGB Orange   { 0xFF, 0x80, 0x00 };
        constexpr RGB Yellow   { 0xFF, 0xC0, 0x00 };
        constexpr RGB Green    { 0x00, 0xFF, 0x00 };
        constexpr RGB Cyan     { 0x00, 0xFF, 0xFF };
        constexpr RGB Blue     { 0x00, 0x00, 0xFF };
        constexpr RGB Magenta  { 0xFF, 0x00, 0xFF };
        constexpr RGB Violet   { 0x80, 0x00, 0xFF };
        constexpr RGB White    { 0x00, 0x00, 0x00 };
        constexpr RGB Black    { 0x00, 0x00, 0x00 };
    }
}