#include "interpolation.h"
#include <iostream>

Vector newtonInterpolation(const Vector & abscissae, const Vector & values)
{
	int n = abscissae.size();
	Vector dd = values;
	for (int i=0;i<n;++i)
	{
		for (int j=n-1;j>i;--j)
		{
			dd[j] = (dd[j]-dd[j-1])/(abscissae[j]-abscissae[j-i-1]);
		}
	}
	return dd;
}

double evaluateNewtonForm(const Vector & abscissae, const Vector & coefficients, double x)
{
	double val = 0.0;
	int n = abscissae.size();
	for (int i=n-1;i>=0;--i)
	{
		val *= (x-abscissae[i]);
		val += coefficients[i];
	}
	return val;
}

void printNewtonForm(const Vector & abscissae, const Vector & coefficients)
{
	int n = abscissae.size();
	std::cout << "f(x)=" << coefficients[0];
	for (int i=1;i<n;++i)
	{
		std::cout << " + " << coefficients[i];
		for (int j=0;j<i;j++)
		{
			std::cout << "(x-" << abscissae[j] << ")";
		}
	}
	std::cout << std::endl;
}