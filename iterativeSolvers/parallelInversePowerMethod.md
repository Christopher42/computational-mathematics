**Routine Name:** p_inversePowerMethod

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "iterativeSolversParallel.h"

**Description/Purpose:** 
Using the Inverse Power Method, computes the smallest eigenvalue and associated eigenvector, for some known matrix A. Parallel implementation.

**Input:**
Matrix const &A - input matrix
Vector &x - initial guess at solution.
(int maxIter) - (optional) maximum number of iterations to solution. Defaults to 100.


**Output:**
Modifies x to become the computed eigenvector of A.
Returns a double containing that smallest eigenvalue of A.

**Usage/Example:**

```C++
#include <iostream>
#include "iterativeSolversParallel.h" //contains p_inversePowerMethod
#include "vectorCode.h" //contains printVector()

int main (void)
{
	int n = 2;
	Matrix A{{12,7},{3,4}};
	Vector x(n,.5);

	//Inverse Power Method test
	lambda = p_inversePowerMethod(A,x_0);
	std::cout << "Smallest eigenvalue (by inverse power method) is ";
	std::cout << lambda << std::endl;
}
```
Output from the lines above:
```c++
Smallest eigenvalue (by inverse power method) is 1.90141
```


**Implementation/Code:** The following is the code for p_inversePowerMethod(A, x, (maxIter), (tol));
```c++
double p_inversePowerMethod (Matrix const & A, Vector &x, int maxIter, double tol)
{
	int n = A.size();
	//s = A_inv*x;
	Vector y(n,.5);
	p_jacobi(A,x,y,40);
	double lambda = 0.0;
	double err = 10*tol;
	int k = 0;
	while (k++<maxIter and err > tol)
	{
		// x =  y * / ||y||;
		// double y_norm = vectorNormL2(y);
		// x = vectorScale(y,1.0/y_norm);
		double y_norm = 0.0;
		for (int i=0; i<n; i++)
			y_norm+=y[i]*y[i];
		y_norm = sqrt(y_norm);
		for(int i=0;i<n;i++)
			x[i] = y[i]*(1/y_norm);
		
		// Vector s = A_inv*x;
		Vector s(n,.5);
		p_jacobi(A,x,s,40);

		// lambda_new = dotProduct(x,s);
		double lambda_new = 0.0;
		for(int i=0;i<n;++i)
			lambda_new+=x[i]*s[i];

		err = abs(lambda - lambda_new);
		lambda = lambda_new;
	}
	return (1/lambda);
}
```
**Last Modified:** November/2017