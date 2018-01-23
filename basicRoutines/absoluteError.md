**Routine Name:** absoluteError

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "error.h"

**Description/Purpose:** calculates absolute error of an approximation of value x_bar by x.

**Input:**
Exact value x_bar and approximation x - both double type.

**Output:**
Return the absolute error of the approximation as a double type

**Usage/Example:**

```C++
#include <iostream>
#include "error.h"

int main (void)
{
	const double PI=3.141592653589793238462643;
	double x = 3.14; 
	std::cout << "Absolute error in a 3 digit approximation of PI is " << absoluteError(PI,x) << "\n";
}
```
Output from the lines above:
```c++
Absolute error in a 3 digit approximation of PI is 0.00159265
```


**Implementation/Code:** The following is the code for absoluteError(xbar, x)
```c++
double absoluteError(double xbar, double x)
{
	return std::abs(xbar-x);
}
```
**Last Modified:** Jan/2018
