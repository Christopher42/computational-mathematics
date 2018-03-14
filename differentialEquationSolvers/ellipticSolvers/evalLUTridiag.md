**Routine Name:** evalLUTridiag

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** tridiag.h

**Description/Purpose:** 
Computed a solution to a matrix equation, where the matrix is tridiagonal and factored into LU form.

**Input:**
TridiagSys struct, modified to LU form.
std::vector<double> of function values at mesh points (as produced in init method)

**Output:**
`std::vector<double>` of computed approximations of u(x) at mesh points.

**Usage/Example:**

Tests from TridiagTest.cpp

```C++
#include <iostream>
#include "tridiag.h"

double f (double x)
{
	return sin(x*3.14159);
}

void printVector (std::vector<double> x)
{
	std::cout << '[' << x[0];
	for (int i=1;i<x.size();++i)
		std::cout << ", " << x[i];
	std::cout << ']' << std::endl;
}

void testSimpleElliptic(int m)
{
	double a = 0;
	double b = 1;
	double ua = 2.5;
	double ub = 5.0;
	TridiagSys A = initSimpleElliptic(m, a, b, f, ua, ub);
	TridiagSys ts = A;
	std::vector<double> v = evalLUTridiag(ts, ts.b);
	printVector(v);
}

int main (void)
{
	for (int i=1;i<6;++i)
	{
		std::cout << "With mesh of " << i << std::endl;
		testSimpleElliptic(i);
		std::cout << std::endl;
	}
```
Output from the lines above:
```c++
With mesh of 1
[1.75]

With mesh of 2
[-4.4609, -3.62757]

With mesh of 3
[-16.1887, -23.5637, -14.9387]
```


**Implementation/Code:** The following is the code for luTridiag
```c++
std::vector<double> evalLUTridiag(TridiagSys A, std::vector<double> b)
{
	std::vector<double> sol = b;
	for (int i=1;i<A.n;++i)
	{
		sol[i]-=A.lower[i]*sol[i-1];
	}
	sol[n-1]/=A.middle[n-1];
	for(int i=n-2;i>=0;--i)
	{
		sol[i]=(sol[i]-A.upper[i]*sol[i+1])/A.middle[i];
	}
	return sol;
} 
```
**Last Modified:** February/2018
