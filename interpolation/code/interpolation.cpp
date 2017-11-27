#include "interpolation.h"

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