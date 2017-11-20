#ifndef ITERATIVE_SOLVERS_PARALLEL_H
#define ITERATIVE_SOLVERS_PARALLEL_H

#include <cmath>
#include <vector>

typedef std::vector<double> Vector;
typedef std::vector<std::vector<double>> Matrix;

int p_jacobi(Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-8.0));
int p_gaussSeidel(Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-8.0));
int p_steepestDescent (Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-8.0));
int p_conjugateGradient (Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-10.0));

double p_powerMethod (Matrix const & A, Vector &x, int maxIter=100, double tol=pow(10.0,-10.0));
double p_inversePowerMethod (Matrix const & A, Vector &x, int maxIter=100, double tol=pow(10.0,-10.0));
#endif