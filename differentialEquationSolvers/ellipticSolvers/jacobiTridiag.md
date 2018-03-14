**Routine Name:** jacobiTridiag

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** tridiag.h

**Description/Purpose:**
Solves a tridiagonal system using jacobi iteration

**Input:**
TridiagSys Struct - produced by initSimpleElliptic or initElliptic.

**Output:**
`std::vector<double>`, giving the approximated values of u(x) at each point of the mesh.

**Usage/Example:**

```C++
#include <iostream>
#include "tridiag.h"

double f (double x)
{
	return sin(x*3.14159);
}

double k (double x)
{
	return 1;
}

void printVector (std::vector<double> x)
{
	std::cout << '[' << x[0];
	for (int i=1;i<x.size();++i)
		std::cout << ", " << x[i];
	std::cout << ']' << std::endl;
}

void printElliptic(TridiagSys A)
{
	std::cout << "Upper diagonal: [";
	printVector(A.upper);
	std::cout << "Main diagonal: [";
	printVector(A.main);
	std::cout << "Lower diagonal: [";
	printVector(A.lower);
	std::cout << "Mesh: [";
	printVector(A.mesh);
	std::cout << "B: [";
	printVector(A.b);
}

void testSimpleElliptic(int m)
{
	double a = 0;
	double b = 1;
	double ua = 2.5;
	double ub = 5.0;
	TridiagSys A = initSimpleElliptic(m, a, b, f, ua, ub);
	TridiagSys ts = A;
	std::vector<double> ts=A;
	v = jacobiTridiag(ts);
}

int main (void)
{
	for (int i=1;i<4;++i)
	{
		std::cout << "With mesh of " << i << std::endl;
		testSimpleElliptic(i);
		// testElliptic(i);
		std::cout << std::endl;
	}

	return 0;
}
```
Output from the lines above:
```c++
With mesh of 1
[1.75]

With mesh of 2
[-2.64711, -1.39712]

With mesh of 3
[-4.40685, -11.7819, -3.15687]
```


**Implementation/Code:** The following is the code for jacobiTridiag
```c++
std::vector<double> jacobiTridiag(TridiagSys A, int maxIter, double tol)
{
	int n=A.n;

	double err=10*tol;
	std::vector<double> x(A.n);
	std::vector<double> xold=x;
	int k=0;

	while(k++<maxiter and err>tol*tol)
	{
		x=A.b;
		for (int i=0;i<n-1;++i)
		x[i]-=A.lower[i]*xold[i+1];
		for (int i=1;i<n;++i)
		x[i]-=A.upper[i]*x_old[i-1];
		for(int i=0;i<n;++i)
		x[i]\=A.main[i];

		err=0.0;
		for (int i=0;i<n;++i)
		err+=(x[i]-xold[i])*(x[i]-xold[i]);
		xold=x;
	}
	return x;
}
```
**Last Modified:** February/2018
