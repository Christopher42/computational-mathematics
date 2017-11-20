#include "matrix.h"
#include "vectorCode.h"
#include <iostream>

int main (void)
{
	Matrix a;
	a.push_back(Vector({1,2}));
	a.push_back(Vector({1,1}));
	std::cout << "Let A be defined as the matrix\n";
	printMatrix(a);
	std::cout << "Then the l1 matrix norm of A is " << matrixNormL1(a) << " and the l-infinity matrix norm of A is " << matrixNormLInf(a) << std::endl;
	std::cout << std::endl;

	Matrix b(5, Vector(5,1));
	std::cout << "Now, let B denote the matrix" << std::endl;
	printMatrix(b);
	std::cout << "The matrix sum A+2B is therefore\n";
	printMatrix(matrixAdd(a,matrixScale(b,2)));
	std::cout << std::endl;

	Vector v{1,2,3,4,5};
	std::cout << "Now, let v denote the vector\n";
	printVector(v);
	std::cout << "(B+I)*v is therefore\n";
	Matrix I_5 = identityMatrix(5);
	printVector(matrixVectorProduct(matrixAdd(b,I_5),v));
	std::cout << std::endl;

	Matrix c = {{1,2,3},{4,5,6}};
	Matrix d = {{7,8},{9,10},{11,12}};
	std::cout << "Now we will consider the matrix-matrix product of matrices c and d. c is given as\n";
	printMatrix(c);
	std::cout << "and d is given as\n";
	printMatrix(d);
	std::cout << "Their product is therefore\n";
	printMatrix(matrixMatrixProduct(c,d));

	return 0;
}