#include "geometry.h"

// Sphere
//==============================================================================
Sphere::Sphere() {

}


Sphere::Sphere(const Vector& center, const double r, const ColorRGB& color, const int material) {
  this->center = center;
  this->r = r;
  this->color = color;
  this->material = material;
}


int GetSphereIntersections(const Sphere& sphere, const Vector& start, const Vector& dir, Vector* first, Vector* second) {
  assert(first);
  assert(second);

  double a = dir * dir;
  double b = 2 * dir * (start - sphere.center);
  double c = start * start + sphere.center * sphere.center - sphere.center * start * 2 - sphere.r * sphere.r;

  double x1 = 0;
  double x2 = 0;

  int n_roots = SolveQuade(a, b, c, &x1, &x2);
  if (n_roots == INF_SOL || !n_roots)
    return n_roots;
  
  *first = start +  x1 * dir;
  if (n_roots == 2)
    *second = start +  x2 * dir;

  return n_roots;
}

//==============================================================================


// Vector
//==============================================================================
// Constructors & Destructors
//==============================================================================
Vector::Vector() {
}

Vector::Vector(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}
//==============================================================================


// Setters
//==============================================================================
void Vector::SetX(double x) {
  this->x = x;
}

void Vector::SetY(double y) {
  this->y = y;
}

void Vector::SetZ(double z) {
  this->z = z;
}
//==============================================================================


// Getters
//==============================================================================
double Vector::GetX() const {
  return x;
}

double Vector::GetY() const {
  return y;
}

double Vector::GetZ() const {
  return z;
}

double Vector::Length() const {
  return sqrt(x * x + y * y + z * z);
}
//==============================================================================


// Vector operators
//==============================================================================
Vector& Vector::operator += (const Vector& right) {
  x += right.x;
  y += right.y;
  z += right.z;
  return *this;
}


Vector& Vector::operator -= (const Vector& right) {
  x -= right.x;
  y -= right.y;
  z -= right.z;
  return *this;
}


Vector& Vector::operator *= (const double scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}


Vector& Vector::operator ^= (const Vector& right) {
  double res_x = y * right.z - z * right.y;
  double res_y = z * right.x - x * right.z;
  double res_z = x * right.y - y * right.x;
  this->x = res_x;
  this->y = res_y;
  this->z = res_z;
  return *this;
}


Vector Vector::operator - () const {
  return Vector(-x, -y, -z);
}


bool Vector::operator == (const Vector& right) const {
  return x == right.x &&
         y == right.y &&
         z == right.z;
}


Vector Vector::operator + (const Vector& right) const {
  return Vector(
    x + right.x,
    y + right.y,
    z + right.z
  );
}


Vector Vector::operator - (const Vector& right) const {
  return Vector(
    x - right.x,
    y - right.y,
    z - right.z
  );
}


Vector Vector::operator * (const double scalar) const {
  return Vector(
    x * scalar,
    y * scalar,
    z * scalar
  );
}


double Vector::operator * (const Vector& right) const {
  return x * right.x +
         y * right.y +
         z * right.z;
}


Vector Vector::operator ^ (const Vector& right) const {
  Vector res = *this;
  res ^= right;
  return res;
}


Vector operator * (const double scalar, const Vector& vector) {
  Vector res = vector;
  res *= scalar;
  return res;
}
//==============================================================================


// Other member functions
//==============================================================================
void Vector::Normalize() {
  double length = Length();
  if (length) {
    x /= length;
    y /= length;
    z /= length;
  }
}

void Vector::Resize(double new_length) {
  Normalize();
  (*this) *= new_length;
}

void Vector::Reflect(const Vector& normal) {
  (*this) = 2 * (normal * *this) * normal - (*this);
}
// void Vector::Reflect(const Vector& normal) {
//   (*this) = -(*this) - (-(*this) * normal) * normal * 2;
// }
//==============================================================================


// Trigonometry
//==============================================================================
double VectorsCos(const Vector& first, const Vector& second) {
  double numerator = first * second;
  if (!numerator)
    return 0;
  return numerator / (first.Length() * second.Length());
}


double VectorsSin(const Vector& first, const Vector& second) {
  double cos = VectorsCos(first, second);
  return sqrt(1 - cos * cos);
}
//==============================================================================
//==============================================================================


// Geometry
//==============================================================================
int GetSphereIntersecs(const Sphere& sphere, const Vector& start, const Vector& dir, Vector* first, Vector* second) {
  assert(first);
  assert(second);

  double a = dir * dir;
  double b = 2 * dir * (start - sphere.center);
  double c = start * start + sphere.center * sphere.center - 2 * sphere.center * start - sphere.r * sphere.r;

  double x1 = 0;
  double x2 = 0;

  int n_roots = SolveQuade(a, b, c, &x1, &x2);
  if (n_roots == INF_SOL || !n_roots)
    return n_roots;

  *first = start + x1 * dir;
  if (n_roots == 2)
    *second = start + x2 * dir;

  return n_roots;
}
//==============================================================================
