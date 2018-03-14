**Routine Name:** initSimpleElliptic

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** tridiag.h

**Description/Purpose:**
Generates and Populates a TridiagSys struct with information needed to solve the simple elliptic problem (u''=f(x)).

**Input:**
int m - mesh size
doubles a,b - endpoints for the interval
`double (*f)(double)` - input function for the elliptic function
doubles u_a,u_b - u(a) and u(b)

**Output:**
TridiagSys - tridiagonal matrix system struct with all information needed for solving. Several solvers take this as input.

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
	printElliptic(A);
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
Upper diagonal: [[0]
Main diagonal: [[-2]
Lower diagonal: [[0]
Mesh: [[0.5]
B: [[-3.5]

With mesh of 2
Upper diagonal: [[1, 0]
Main diagonal: [[-2, -2]
Lower diagonal: [[0, 1]
Mesh: [[0.333333, 0.666667]
B: [[5.29422, 2.79424]

With mesh of 3
Upper diagonal: [[1, 1, 0]
Main diagonal: [[-2, -2, -2]
Lower diagonal: [[0, 1, 1]
Mesh: [[0.25, 0.5, 0.75]
B: [[8.8137, 16, 6.31373]   
```


**Implementation/Code:** The following is the code for initSimpleElliptic.
```c++
struct TridiagSys {
	int n;
	std::vector<double> main;
	std::vector<double> upper;
	std::vector<double> lower;
	std::vector<double> mesh;
	std::vector<double> b;
}

TridiagSys initSimpleElliptic(int m, double a, double b, double (f*)(double), double u_a, double u_b)
{
	TridaigSys system;
	system.n=m;
	system.main = std::vector<double>(m,-2);

	system.upper = std::vector<double>(m,1);
	system.upper[m-1]=0;

	system.lower = std::vector<double>(m,1);
	system.lower[0]=0;

	double h = 1.0/(1+m);
	std::vector<double> mesh(m);
	std::vector<double> b(m);
	for(int i=0;i<m;++i)
	{
		mesh[i]=((b-a)*(i+1))/(m+1)
		b[i]=f(mesh[i])/(h*h);
	}
	b[0]-= u_a;
	b[m-1]-= u_b;
	system.b = b;
	system.mesh = mesh;
	return system;
}
    
```
**Last Modified:** February/2018
