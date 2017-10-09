#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "vectorCode.h"

typedef std::vector<std::vector<double>> Matrix;

double matrixNormL1 (Matrix m);
double matrixNormLInf (Matrix m);

void printMatrix (Matrix m);
Matrix identityMatrix(int n);

Matrix matrixAdd(Matrix a, Matrix b);
Matrix matrixSub(Matrix a, Matrix b);
Matrix matrixScale(Matrix a, double s);
Vector matrixVectorProduct(Matrix a, Vector v);
Matrix matrixMatrixProduct(Matrix a, Matrix b);

#endif