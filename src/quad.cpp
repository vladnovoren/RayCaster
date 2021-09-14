#include "quad.h"


bool IsZero(double x) {
  return fabsf64(x) < eps;
}

double Discrim(double a, double b, double c){
    return b * b - 4 * a * c;
}

int SolveQuade(double a, double b, double c, double* x1, double* x2) {
  assert(std::isfinite(b));
  assert(std::isfinite(c));

  assert(x1);
  assert(x2);
  assert(x1 != x2);

  if (IsZero(a)) {
    if (IsZero(b)) {
      if (IsZero(c))
        return INF_SOL;
      else
        return NO_SOL;
    } else { // b != 0
      *x1 = *x2 = - c / b;
      return ONE_SOL;
    }
  } else { // a != 0
    double discrim = Discrim(a, b, c);

    if (discrim < 0)
      return NO_SOL;

    if (IsZero(discrim)) {
      *x1 = *x2 = - b / (2 * a);
      return ONE_SOL;
    }

    if (discrim > 0) {
      double sqrt_discrim = sqrt(discrim);
      *x1 = (-b + sqrt_discrim)/(2 * a);
      *x2 = (-b - sqrt_discrim)/(2 * a);
      return TWO_SOL;
    }
  }
  return NO_SOL;
}