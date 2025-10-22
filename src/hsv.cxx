#include "colors.hxx"
#include "detail/fakestd.hxx"

using namespace Colors;

void HSV::FromRgb(const RGB& rgb, Fix16& hue, Fix16& sat, Fix16& val)
{
    Fix16 rNorm = Fix16(rgb.r) / F16(255.0);
    Fix16 gNorm = Fix16(rgb.g) / F16(255.0);
    Fix16 bNorm = Fix16(rgb.b) / F16(255.0);

    auto max = Detail::max(rNorm, gNorm, bNorm);
    auto min = Detail::min(rNorm, gNorm, bNorm);
    auto delta = max - min;

    val = max;
    sat = (max == F16(0.0)) ? F16(0.0) : Fix16(delta / max).value;

    if (delta != F16(0.0))
    {
        if (max == rNorm)
        {
            hue = F16(60.0f) * fix16_mod(((gNorm - bNorm) / delta), F16(6.0));
        }
        else if (max == gNorm)
        {
            hue = Fix16(F16(60.0f)) * Fix16((bNorm - rNorm) / delta) + F16(2.0);
        }
        else
        {
            hue = Fix16(F16(60.0f)) * Fix16((rNorm - gNorm) / delta) + F16(4.0);
        }
    }

    if (hue < F16(0.0))
    {
        hue += F16(360.0);
    }
}

HSV::HSV(const RGB& rgb)
{
    FromRgb(rgb, h, s, v);
}

HSV& HSV::operator=(const RGB& rgb)
{
    FromRgb(rgb, h, s, v);
    return *this;
}

RGB HSV::ToRGB(const HSV& hsv)
{
    auto chroma = hsv.v * hsv.s;
    auto hPrime = hsv.h / F16(60.0);
    auto x = chroma * (Fix16(1) - fix16_abs(fix16_mod(hPrime, F16(2.0)) - F16(1)));
    auto m = hsv.v - chroma;

    Fix16 rPrime, gPrime, bPrime;

    if (hPrime >= F16(0) && hPrime < F16(1)) 
    {
        rPrime = chroma; gPrime = x; bPrime = F16(0);
    } 
    else if (hPrime >= F16(1) && hPrime < F16(2)) 
    {
        rPrime = x; gPrime = chroma; bPrime = F16(0);
    } 
    else if (hPrime >= F16(2) && hPrime < F16(3)) 
    {
        rPrime = F16(0); gPrime = chroma; bPrime = x;
    } 
    else if (hPrime >= F16(3) && hPrime < F16(4)) 
    {
        rPrime = F16(0); gPrime = x; bPrime = chroma;
    } 
    else if (hPrime >= F16(4) && hPrime < F16(5)) 
    {
        rPrime = x; gPrime = F16(0); bPrime = chroma;
    } 
    else {
        rPrime = chroma; gPrime = F16(0); bPrime = x;
    }

    auto r = (rPrime + m) * F16(255);
    auto g = (gPrime + m) * F16(255);
    auto b = (bPrime + m) * F16(255);

    return RGB(fix16_to_int(r), fix16_to_int(g), fix16_to_int(b));
}

HSV HSV::GammaCorrection(const HSV& hsv)
{
    auto rgb = hsv.ToRGB();
    return HSV(rgb.GammaCorrection());
}