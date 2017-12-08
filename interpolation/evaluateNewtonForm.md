**Routine Name:** evaluateNewtonForm

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** ["interpolation.h"](https://github.com/Christopher42/computational-mathematics/blob/master/interpolation/code/interpolation.h)

**Description/Purpose:** 
Given the Newton form of the polynomial, evaluate at a given point. Note that this form should be used only for interpolation, never extrapolation.

**Input:**
const Vector & abscissae - vector of abscissae.
const Vector & coefficients - vector of function values at abscissae.

**Output:**
Returns a double, indicating the computed value at the point.

**Usage/Example:**
The example given below is worked through by hand on [wikipedia](https://en.wikipedia.org/wiki/Newton_polynomial). It is the last problem in the examples section.
```C++
#include <iostream>
#include "interpolation.h" //contains newtonInterpolation
#include "vectorCode.h" //contains printVector()

int main (void)
{
	Vector abscissae ({1,2,3,4});
	Vector values ({6,9,2,5});
	Vector coefficients = newtonInterpolation(abscissae, values);
	std::cout << "calculating values of the functions at the following x values:\n";
	for (double i=1;i<=4;i=i+.5)
	{
		double y = evaluateNewtonForm(abscissae, coefficients,i);
		std::cout << "x=" << i << "\t" << y << std::endl;
	}
}
```
Output from the lines above:
```C++
calculating values of the functions at the following x values:
x=1 	6
x=1.5	10
x=2 	9
x=2.5	5.5
x=3 	2
x=3.5	1
```
Note that the interpolating polynomial takes the original input values at the abscissae.

**Implementation/Code:** The following is the code for double evaluateNewtonForm(abscissae, coefficients, double x)
```c++
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
```
**Last Modified:** November/2017
