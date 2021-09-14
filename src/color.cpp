#include "color.h"


ColorRGB::ColorRGB() {

}


ColorRGB::ColorRGB(double r, double g, double b) {
  this->r = r;
  this->g = g;
  this->b = b;
}


ColorRGB& ColorRGB::operator *= (const double mul) {
  r *= mul;
  g *= mul;
  b *= mul;
  return *this;
}


ColorRGB& ColorRGB::operator *= (const ColorRGB& right) {
  r *= right.r;
  g *= right.g;
  b *= right.b;
  return *this;
}


ColorRGB& ColorRGB::operator += (const ColorRGB& right) {
  r += right.r;
  g += right.g;
  b += right.b;
  return *this;
}


ColorRGB ColorRGB::operator + (const ColorRGB& right) const {
  return ColorRGB(
    r + right.r,
    g + right.g,
    b + right.b
  );
}


ColorRGB ColorRGB::operator * (const ColorRGB& right) const {
  return ColorRGB(
    r * right.r,
    g * right.g,
    b * right.b
  );
}


ColorRGB ColorRGB::operator * (const double scalar) const {
  return ColorRGB(
    r * scalar,
    g * scalar,
    b * scalar
  );
}


void ColorRGB::Format() {
  r = Min(r * 255, 255);
  g = Min(g * 255, 255);
  b = Min(b * 255, 255);
}


ColorRGB operator * (const double scalar, const ColorRGB& color) {
  return ColorRGB(
    scalar * color.r,
    scalar * color.g,
    scalar * color.b
  );
}


double Min(const double first, const double second) {
  return first < second ? first : second;
}


double Max(const double first, const double second) {
  return first > second ? first : second;
}
