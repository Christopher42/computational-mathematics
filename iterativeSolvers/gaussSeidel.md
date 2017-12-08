**Routine Name:** gaussSeidel

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "iterativeSolvers.h"

**Description/Purpose:** 
Using the Gauss-Seidel method, Computes an approximate solution to the equation Ax=b, where A and b are known.

**Input:**
Matrix const &A - input matrix
Vector const &b - target solution of matrix
Vector &x - initial guess at solution.
(int maxIter) - (optional) maximum number of iterations to solution. Defaults to n, the size of matrix.


**Output:**
Modifies x to become the computed approximate solution to Ax=b.
Returns an int indicating the number of iterations to solution.

**Usage/Example:**

```C++
#include <iostream>
#include "iterativeSolvers.h" //this contains gaussSeidel Method
#include "vectorCode.h" //contains printVector()

int main (void)
{
	Matrix A{ {500,1,1},{1,500,1},{1,1,500} };
	Vector b{1004,1004,1004};
	Vector x{1,1,1};

	//Gauss-Seidel test
	int i = gaussSeidel(A,b,x,25);
	std::cout << i << " iterations to solution.\n";
	printVector(x);
}
```
Output from the lines above:
```c++
5 iterations to solution.
[2, 2, 2]
```


**Implementation/Code:** The following is the code for gaussSeider(A, b, x, (maxIter), (tol))
```c++
int gaussSeidel (Matrix const &A, Vector const &b, Vector & x, int maxIter, double tol)
{
	int n = A.size();
	if (maxIter == 0)
		maxIter = n;
	double err = 10*tol;
	Vector x_old = x;
	int k=0;

	while (k++<maxIter and err>tol*tol)
	{
		for (int i=0;i<n;++i)
		{
			double sum = 0;
			for (int j=0;j<i;++j)
				sum+=A[i][j]*x[j];
			for (int j=i+1;j<n;++j)
				sum+=A[i][j]*x[j];
			x[i]=(b[i]-sum)/A[i][i];
		}

		// err = error^2 = L2err(x,x_old)^2
		err = 0.0;
		for (int i=0;i<n;++i)
			err += (x[i]-x_old[i])*(x[i]-x_old[i]);
		x_old = x;
	}
	return k;
}
```
**Last Modified:** November/2017
