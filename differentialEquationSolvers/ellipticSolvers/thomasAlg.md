**Routine Name:** thomasAlg

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** tridiag.cpp

**Description/Purpose:**
Solves a tridiagonal matrix system using Thomas algorithm (a special case of Gaussian Elimination).

**Input:**
Takes a TridiagSys struct produced by an appropriaate init method.

**Output:**
`std::vector<double>` containing computed approximations of u(x) at each point in the mesh

**Usage/Example:**

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
	std::vector<double> v = thomasAlg(ts);
	printVector(v);
}

int main (void)
{
	for (int i=1;i<4;++i)
	{
		std::cout << "With mesh of " << i << std::endl;
		testSimpleElliptic(i);
		std::cout << std::endl;
	}

	return 0;
}
```
Output from the lines above:
```c++
With mesh of 1
[-0.875]

With mesh of 2
[1.32356, -0.653636]

With mesh of 3
[2.20343, -6.13181, -8.00071]
```


**Implementation/Code:** The following is the code for thomasAlg
```c++
std::vector<double> thomasAlg(TridiagSys A)
{
	int n = A.n;
	std::vector<double> x = A.b;
	std::vector<double> c = A.upper;

	c[0]/= A.main[0];
	for (int i=0;i<n;++i)
	{
		c[i]/=(A.main[i]-A.lower[i]*c[i-1]);
	}

	x[0] /=A.main[0];
	for (int i=0;i<n;++i)
	{
		x[i]=(x[i]-A.lower[i]*x[i-1])/(A.main[i]-A.lower[i]*c[i-1]);
	}

	return x;
}
```
**Last Modified:** February/2018
