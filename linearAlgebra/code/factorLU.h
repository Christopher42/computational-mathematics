#ifndef FACTORLU_H
#define FACTORLU_H

#include <vector>

typedef std::vector<double> Vector;
typedef std::vector<std::vector<double>> Matrix;

Vector factorLUWithPartialPivot (Matrix &A);
Matrix verifyLU(const Matrix &m, Vector p);

#endif