**Routine Name:** newtonInterpolation

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "interpolation.h"

**Description/Purpose:** 
Using the Newton form, computes a polynomial interpolation of data points.

**Input:**
const Vector & abscissae - vector of abscissae.
const Vector & value - vector of function values at abscissae.

**Output:**
Returns a Vector containing the coefficients of the Newton form. This vector and the abscissae vector may be used as inputs for evaluateNewtonForm to determine the value of the interpolated function at a point.

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
	printVector(coefficients);
}
```
Output from the lines above:
```C++
[6, 3, -5, 3.33333]
```


**Implementation/Code:** The following is the code for newtonInterpolation(abscissae, value)
```c++
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
```
**Last Modified:** November/2017