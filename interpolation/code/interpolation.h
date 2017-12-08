#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>

typedef std::vector<double> Vector;

Vector newtonInterpolation(const Vector & abscissae, const Vector & values);
double evaluateNewtonForm(const Vector & abscissae, const Vector & coefficients, double x);
void printNewtonForm(const Vector & abscissae, const Vector & coefficients);


#endif