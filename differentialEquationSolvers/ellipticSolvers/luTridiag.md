**Routine Name:** luTridiag

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** tridiag.h

**Description/Purpose:** 
Computes an LU factorization of a tridaigonal matrix.

**Input:**
TridiagSys struct, produced by initSimpleElliptic or initElliptic.

**Output:**
No return. Modifies the input TridiagSys in place to the LU representation. Used in conjunction with evalLUTridiag, it will produce a solution vector.

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
	TridiagSys ts=A;
	luTridiag(ts);
	v = evalLUTridiag(ts, ts.b);
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
[1.75]

With mesh of 2
[-4.4609, -3.62757]

With mesh of 3
[-16.1887, -23.5637, -14.9387]
```


**Implementation/Code:** The following is the code for luTridiag
```c++
void luTridiag(TridiagSys& A)
{
	int n=A.n;
	for(int i=1;i<n;++i)
	{
		lower[i]/=middle[i-1];
		main[i]-=lower[i]*upper[i-1];
	}
	return;
}  
```
**Last Modified:** February/2018
