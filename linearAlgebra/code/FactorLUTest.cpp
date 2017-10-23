#include <iostream>
#include "matrix.h"
#include "factorLU.h"

int main(void)
{
	Vector m0 = {3,2,1};
	Vector m1 = {6,5,4};
	Vector m2 = {27,8,7};
	Matrix m = {m0,m1,m2};
	std::cout << "Starting with matrix m = \n";
	printMatrix(m);
	Vector p = factorLUWithPartialPivot(m);
	verifyLU(m,p);
    return 0;
}