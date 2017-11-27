#include <iostream>
#include "interpolation.h"
#include "vectorCode.h"

int main (void)
{
	Vector abscissae ({1,2,3,4});
	Vector values ({6,9,2,5});
	Vector coefficients = newtonInterpolation(abscissae, values);
	printVector(coefficients);
	std::cout << "calculating values of the functions at the following x values:\n";
	for (double i=1;i<=4;i=i+.5)
	{
		double y = evaluateNewtonForm(abscissae, coefficients,i);
		std::cout << "x=" << i << "\t" << y << std::endl;
	}
}