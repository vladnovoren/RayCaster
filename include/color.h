#ifndef COLOR_H
#define COLOR_H


struct ColorRGB {
  double r = 0;
  double g = 0;
  double b = 0;

  ColorRGB();

  ColorRGB(double r, double g, double b);

  ColorRGB& operator *= (const double mul);

  ColorRGB& operator *= (const ColorRGB& right);

  ColorRGB& operator += (const ColorRGB& right);

  ColorRGB operator + (const ColorRGB& right) const;

  ColorRGB operator * (const ColorRGB& right) const;

  ColorRGB operator * (const double scalar) const;

  friend ColorRGB operator * (const double scalar, const ColorRGB& color);

  void Format();
};


double Min(const double first, const double second);

double Max(const double first, const double second);


#endif /* color.h */
