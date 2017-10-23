#ifndef PARALLEL_MATRIX_OPERATION_H
#define PARALLEL_MATRIX_OPERATION_H

typedef std::vector<double> Vector;
typedef std::vector<std::vector<double>> Matrix;

Vector parallelMatrixVectorProduct(const Matrix &a, const Vector &v);
Matrix parallelMatrixMatrixProduct(const Matrix &a, const Matrix &b);
Matrix randMatrix(int n, int m);
Vector randVector(int n);

#endif