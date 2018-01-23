#include <cmath>

double absoluteError(double computed, double expected)
{
	return std::abs(computed-expected);
}

double relativeError(double computed, double expected)
{
	return std::abs(computed-expected)/expected;
}

double nestedPolynomialEvaluation (double x, int size, double A[])
{
	double result = A[size-1];
	for (int i=size-2; i>-1; i--)
	{
		result = result*x + A[i];
	}
	return result;
}