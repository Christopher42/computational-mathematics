#include <iostream>
#include "interpolation.h"
#include "vectorCode.h"

void runSampleInterpolation (void)
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

double rungeFunction (double x)
{
	return 1/(1+25*x*x);
}

void testRungePhenomenon (int k)
{
	Vector abscissae(k+1);
	Vector values(k+1);
	for (int i=0;i<k+1;++i)
	{
		abscissae[i]= (2.0*i)/k-1;
		values[i]=rungeFunction(abscissae[i]);
	}
	Vector coefficients = newtonInterpolation(abscissae, values);
	// printNewtonForm(abscissae, coefficients);
	printNewtonForm(abscissae, coefficients);
}

int main (void)
{
	runSampleInterpolation();
	testRungePhenomenon(5);
	testRungePhenomenon(9);
	testRungePhenomenon(13);
}