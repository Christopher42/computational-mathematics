**Routine Name:** initElliptic

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** tridiag.h

**Description/Purpose:**
Generates and Populates a TridiagSys struct with information needed to solve the complete elliptic problem `(du/dx(u'k(x))=f(x)).`

**Input:**
int m - mesh size
doubles a,b - endpoints for the interval
`double (*f)(double)` - input function
`double (*k)(double)` - input function
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

void testElliptic(int m)
{
	double a = 0;
	double b = 1;
	double ua = 2.5;
	double ub = 5.0;
	TridiagSys A = initElliptic(m, a, b, f, k, ua, ub);
	printElliptic(A);
}

int main (void)
{
	for (int i=1;i<4;++i)
	{
		std::cout << "With mesh of " << i << std::endl;
		testElliptic(i);
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



**Implementation/Code:** The following is the code for initElliptic.
```c++
TridiagSys initElliptic(int m, double a, double b, double (f*)(double), double (k*)(double), double u_a, double u_b)
{
	TridaigSys system;
	system.n=m;

	std::vector<double> mesh(m);
	std::vector<double> b(m);
	for(int i=0;i<m;++i)
	{
		mesh[i]=((b-a)*(i+1))/(m+1)
		b[i]=f(mesh[i])/((1+m)*(1+m)); //times h^2
	}
	b[0]-= u_a;
	b[m-1]-= u_b;
	system.b = b;
	system.mesh = mesh;

	system.main = std::vector<double>(m,-2);

	system.upper = std::vector<double>(m,0);
	system.lower = std::vector<double>(m,0);
	system.lower[0]=k((u_a+mesh[0])/2);
	system.upper[n-1]=k((mesh[n-1]+u_b)/2);
	for (int i=0;i<m-2;++i)
	{
		system.lower[i+1]=system.upper[i]=k((mesh[i]+mesh[i+1])/2);
		system.main[i]=(system.lower[i]+system.upper[i])/2;
	}
	system.lower[0]=0;
	system.upper[n-1]=0;

	system.lower = std::vector<double>(m,1);
	system.lower[0]=0;

	return system;
}    
```
**Last Modified:** February/2018
