#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "quad.h"
#include "color.h"


//==============================================================================
class Vector {
  double x = 0;
  double y = 0;
  double z = 0;
public:
  // Constructor & destructors
  Vector();

  explicit Vector(double x, double y, double z);

  // Setters
  void SetX(double x);

  void SetY(double y);

  void SetZ(double z);

  // Getters
  double GetX() const;

  double GetY() const;

  double GetZ() const;

  double Length() const;

  // Vector operators
  Vector& operator += (const Vector& right);

  Vector& operator -= (const Vector& right);

  Vector& operator *= (const double scalar);

  Vector& operator *= (const Vector& right);

  Vector& operator ^= (const Vector& right);

  Vector operator - () const;

  bool operator == (const Vector& right) const;

  Vector operator + (const Vector& right) const;

  Vector operator - (const Vector& right) const;

  Vector operator * (const double scalar) const;

  double operator * (const Vector& right) const;

  Vector operator ^ (const Vector& right) const;

  friend Vector operator * (const double scalar, const Vector& vector);

  void Normalize();

  void Resize(double new_length);

  void Reflect(const Vector& normal);
};


Vector operator * (const double scalar, const Vector& vector);

double VectorsCos(const Vector& first, const Vector& second);

double VectorsSin(const Vector& first, const Vector& second);
//==============================================================================


//==============================================================================
struct Sphere {
  Vector center;
  double r;
  ColorRGB color;
  int material;

  Sphere();

  Sphere(const Vector& center, const double r, const ColorRGB& color, const int material);
};

int VectorSphereIntersec(const Sphere& sphere, const Vector& start, const Vector& dir, Vector* intersec);
//==============================================================================


#endif /* geometry.h */