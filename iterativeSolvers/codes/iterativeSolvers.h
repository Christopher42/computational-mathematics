#ifndef ITERATIVE_SOLVERS_H
#define ITERATIVE_SOLVERS_H

#include <cmath>
#include <vector>

typedef std::vector<double> Vector;
typedef std::vector<std::vector<double>> Matrix;

int jacobi(Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-8.0));
int gaussSeidel (Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-8.0));
int steepestDescent (Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-8.0));
int conjugateGradient (Matrix const &A, Vector const &b, Vector & x, int maxIter=0, double tol=pow(10.0,-10.0));
int bonjugateGradient(Matrix const &A, Vector const &b, Vector & x0, int maxIter=0, double tol=pow(10.0,-10.0));
#endif