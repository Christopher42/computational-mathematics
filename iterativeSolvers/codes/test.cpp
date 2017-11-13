#include <iostream>
#include "iterativeSolvers.h" //this contains Jacobi Method
#include "vectorCode.h" //contains printVector()

int main (void)
{
	Matrix A{{500,1,1},{1,500,1},{1,1,500}};
	Vector b{1004,1004,1004};
	Vector x{1,1,1};

	//Jacobi test
	int i = bonjugateGradient(A,b,x,25);
	std::cout << i << " iterations to solution.\n";
	printVector(x);
}