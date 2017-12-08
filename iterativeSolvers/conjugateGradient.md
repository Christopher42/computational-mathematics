**Routine Name:** conjugateGradient

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "iterativeSolvers.h"

**Description/Purpose:** 
Using the Conjugate Gradient method, computes an approximate solution to the equation Ax=b, where A and b are known.

**Input:**
Matrix const &A - input matrix
Vector const &b - target solution of matrix
Vector &x - initial guess at solution.
(int maxIter) - (optional) maximum number of iterations to solution. Defaults to n, the size of matrix.


**Output:**
Modifies x to become the computed approximate solution to Ax=b.
Returns an int indicating the number of iterations to solution.

**Usage/Example:**

{% raw %}
```C++
#include <iostream>
#include "iterativeSolvers.h" //this contains conjugateGradient Method
#include "vectorCode.h" //contains printVector()

int main (void)
{
	Matrix A{{500,1,1},{1,500,1},{1,1,500}};
	Vector b{1004,1004,1004};
	Vector x{1,1,1};

	//Conjugate Gradient test
	int i = conjugateGradient(A,b,x,25);
	std::cout << i << " iterations to solution.\n";
	printVector(x);
}
```
{% endraw %}
Output from the lines above:
```c++
1 iterations to solution.
[2, 2, 2]
```


**Implementation/Code:** The following is the code for conjugateGradient( A, b, x, (maxIter), (tol))
```c++
int conjugateGradient (Matrix const &A, Vector const &b, Vector & x, int maxIter, double tol)
{
	int n = A.size();
	if (maxIter == 0)
		maxIter = n;
	//r_0 = b - Ax
	Vector x1(n,0);
	Vector r = matrixVectorProduct(A,x);
	for (int i=0;i<n;++i)
		r[i] = b[i]-r[i];
	//delta = ||r||_2^2
	double delta = dotProduct(r,r);
	//b_delta = ||b||_2^2
	double b_delta = dotProduct(b,b);
	
	int k=0;
	Vector p = r;

	while (k++<maxIter and delta>tol*tol*b_delta)
	{
		//s_k = A*p_k
		Vector s(n,0);
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)
				s[i]+=A[i][j]*p[j];
		//alpha_k = delta_k / (p_k \dot s_k)
		double alpha = 0;
		for (int i=0;i<n;++i)
			alpha += p[i]*s[i];
		alpha = delta/alpha;
		//x_k+1 = x_k + alpha_k*p_k
		//r_k+1 = r_k - alpha_k*s_k
		for (int i=0;i<n;++i)
		{
			x1[i] = x[i] + alpha*p[i];
			r[i] = r[i] - alpha*s[i];
		}
			
		//delta_k+1 = ||r_k+1||_2^2
		double delta_new = 0;
		for (int i=0;i<n;++i)
			delta+=r[i]*r[i];
		//p_k+1 = r_k+1 + (delta_k+1/delta_k)p_k
		for (int i=0;i<n;++i)
			p[i]=r[i]+(delta_new/delta)*p[i];
		delta = delta_new;
		x = x1;
	}
	return k;
}

```
**Last Modified:** November/2017
