#include "colors.hxx"

using namespace Colors;

RGB::RGB(const HSV& hsv)
{
    *this = hsv.ToRGB();
}

RGB& RGB::operator=(const HSV& hsv)
{
    *this = hsv.ToRGB();
    return *this;
}

HSV RGB::ToHSV(const RGB& rgb)
{
    return HSV(rgb);
}

HSV RGB::ToHSV() const
{
    return ToHSV(*this);
}

RGB::operator HSV() const
{
    return ToHSV();
}