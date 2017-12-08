**Routine Name:** powerMethod

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "iterativeSolvers.h"

**Description/Purpose:** 
Using the Power Method, computes the largest eigenvalue and associated eigenvector, for some known matrix A.

**Input:**
Matrix const &A - input matrix
Vector &x - initial guess at solution.
(int maxIter) - (optional) maximum number of iterations to solution. Defaults to 100.


**Output:**
Modifies x to become the computed eigenvector of A.
Returns a double containing that largest eigenvalue of A.

**Usage/Example:**

```C++
#include <iostream>
#include "iterativeSolvers.h" //contains powerMethod
#include "vectorCode.h" //contains printVector()

int main (void)
{
	int n = 2;
	Matrix A{ {12,7},{3,4} };
	Vector x(n,.5);

	//Power Method test
	double lambda = powerMethod(A,x_0);
	std::cout << "Largest eigenvalue (by power method) is ";
	std::cout << lambda << std::endl;
}
```
Output from the lines above:
```c++
Largest eigenvalue (by power method) is 14.2878
```


**Implementation/Code:** The following is the code for powerMethod(A, x, (maxIter), (tol));
```c++
double powerMethod (Matrix const & A, Vector &x, int maxIter, double tol)
{
	int n = A.size();
	Vector y = matrixVectorProduct(A,x);
	double lambda = 0.0;
	double err = 10*tol;
	int k = 0;
	while (k++<maxIter and err > tol)
	{
		// x =  y * (1/||y||);
		double y_norm = 0.0;
		for (int i=0; i<n; i++)
			y_norm+=y[i]*y[i];
		y_norm = sqrt(y_norm);
		for(int i=0;i<n;i++)
			x[i] = y[i]*(1/y_norm);
		
		// Vector s = A*x;
		Vector s(n,0);
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)
				s[i]+=A[i][j]*x[j];

		// lambda_new = dotProduct(x,s);
		double lambda_new = 0.0;
		for(int i=0;i<n;++i)
			lambda_new+=x[i]*s[i];

		err = abs(lambda - lambda_new);
		lambda = lambda_new;
	}
	return lambda;
}
```
**Last Modified:** November/2017
