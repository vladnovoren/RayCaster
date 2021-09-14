#include "geometry.h"
#include <cstdio>


int main() {
  Vector v1(1, 0, 0);
  Vector v2(0, 1, 0);
  Vector v3 = v1 ^ v2;
  printf("v1 ^ v2:\n");
  printf("x: %lf, y: %lf, z: %lf\n", v3.GetX(), v3.GetY(), v3.GetZ());
  return 0;
}
