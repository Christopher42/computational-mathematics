#include <iostream>
#include <vector>
#include <cmath>
#include "laplacian.h"
#include "iterativeSolvers.h"

double f(double x, double y)
{
	return sin(x*y);
}

void printVec(const Vec& v)
{
	std::cout << v[0];
	for (int i=1;i<v.size();++i)
	{
		std::cout << ' ' << v[i];
	}
	std::cout << std::endl;
}

int main (void)
{
	int m = 3;
	Matrix A;
	Vector F;
	Vector U(m*m);
	initLaplace9(m,A,U,F,f);
	std::cout << gaussSeidel(A,F,U,100,.00000001) << std::endl;
	printVec(U);
	return 0;
}