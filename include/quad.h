#ifndef QUAD_H
#define QUAD_H

#include <cstdio>
#include <cmath>
#include <cassert>


const double eps = 1e-6;
const int INF_SOL = -1;
const int  NO_SOL = 0;
const int ONE_SOL = 1;
const int TWO_SOL = 2;


bool IsZero(double x);

double Discrim(double a, double b, double c);

int SolveQuade(double a, double b, double c, double* x1, double* x2);


#endif /* quad.h */