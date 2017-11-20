#ifndef VECTOR_CODE_H
#define VECTOR_CODE_H

#include<vector>

typedef std::vector<double> Vector;

Vector vectorScale (Vector v, double s);
Vector vectorDiff (Vector u, Vector v);

double vectorNormL1 (Vector v);
double vectorNormL2 (Vector v);
double vectorNormLInf (Vector v);
double vectorErrorL1 (Vector u, Vector v);
double vectorErrorL2 (Vector u, Vector v);
double vectorErrorLInf (Vector u, Vector v);
double dotProduct (Vector u, Vector v);
void printVector (Vector v);

#endif