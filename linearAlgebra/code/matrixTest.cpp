#include "matrix.h"
#include <iostream>

int main (void)
{
	Matrix a(5, Vector{-2,-1,0,1,2});
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
	std::cout << "The matrix vector product Bv is therefore\n";
	printMatrix(matrixVectorProduct(b,v));
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