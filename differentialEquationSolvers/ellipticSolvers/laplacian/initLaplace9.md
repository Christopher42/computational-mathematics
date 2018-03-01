**Routine Name:** initLaplace9

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** laplacian.h

**Description/Purpose:**
Generates matrix system to solve the equation `\del(u) = d^2u/dx^2 + d^2u/dy^2 = f(x)` using 9 point stencil. This system my be solved by any of the methods from the direct or iterative methods section.

**Input:**
int m - number of internal points in each dimension
Matrix A - empty matrix object to be initialized
Vectors U,f - empty vectors to be initialized
function f:RxR->R

**Output:**
Modifies A,U,F such that any solver may be used for AU=F. U is initialized to contain suitable random values for iterative methods.

**Usage/Example:**

<explain conditions of usage>
```C++
#include <iostream>
#include <vector>
#include <cmath>
#include "laplacian.h"
#include "iterativeSolvers.h"

double f(double x, double y)
{
	return sin(x*y);
}

int main (void)
{
	int m = 3;
	Matrix A;
	Vector F;
	Vector U(m*m);
	initLaplace9(m,A,U,F,f);
	gaussSeidel(A,F,U,100,.00000001);
	printVec(U);
	return 0;
}
```
Output from the lines above:
```c++
-1.63191 -2.74451 -2.58893 -2.74451 -4.68379 -4.53999 -2.58893 -4.53999 -4.69224
```


**Implementation/Code:** The following is the code for initLaplace9()
```c++
typedef std::vector<double> Vec;
typedef std::vector<std::vector<double>> Matrix;

//init AU=F, then solve for U
void initLaplace9 (int m, Matrix& A, Vec& U, Vec& F, double(*f)(double,double))
{
	A = Matrix(m*m,Vec(m*m,0));
	U = Vec(m*m,0);
	for (int i=0;i<U.size();++i)
	{
		if(i%2==1)
			U[i]=1;
		else
			U[i]=-1;
	}
	initF(m,f,F);
	for (int i=0;i<F.size();++i)
	{
		F[i]*=6*(m+2)*(m+2);
	}

	//init A
	for (int i=0;i<m;++i)
	{
		for (int j=0;j<m;++j)
		{
			int index = i+j*m;
			A[index][index] = -20;
			if (i+1<m)
				A[index][index+1] = 4;
			if (i-1>=0)
				A[index][index-1] = 4;
			if (j+1<m)
			{
				A[index][index+m] = 4;
				if (i+1<m)
					A[index][index+m+1] = 1;
				if (i-1>=0)
					A[index][index+m-1] = 1;
			}
			if (j-1>=0)
			{
				A[index][index-m] = 4;
				if (i+1<m)
					A[index][index-m+1] = 1;
				if (i-1>=0)
					A[index][index-m-1] = 1;
			}
		}
	}
}

void initF(int m, double(*f)(double,double), Vec& F)
{
	F = Vec(m*m,0);
	for (int i=0;i<m;++i)
	{
		for (int j=0;j<m;++j)
		{
			double x = (i+1.0)/(m+2.0);
			double y = (j+1.0)/(m+2.0);
			int index = i+j*m;
			F[index] = f(x,y);
		}
	}
}
```
**Last Modified:** February/2018
