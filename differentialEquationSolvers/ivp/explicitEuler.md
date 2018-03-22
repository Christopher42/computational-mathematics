**Routine Name:** explicitEuler

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** explicitEuler.hpp

**Description/Purpose:** Use explicit Euler method to compute approximation of solutions to initial value problem.

**Input:**
f(t,v) - function that gives value of y' at a point.
double y0 - intial value of y at time b.
double a,b - start and end points for interval of iteration
double h - step size

**Output:**
timesAndValues - a struct containing members time and value of type `std::vector<double>`. These may be printed with the void function printResultsTable, defined in the same header.

**Usage/Example:**

Testing with Newton Cooling.
```c++
#include "explicitEuler.hpp"

#include <iostream>

double newtonCooling (double time, double temp)
{
	//temp is a function of time, but time is not used directly
	return -0.07*(temp-20);
}

int main (void)
{
	double y0=100;
	double a=0;
	double b=100;
	std::vector<double> hvals = {10,5,2};
	std::cout << "Demonstrating newton's cooling law." << std::endl;
	std::cout << "y0=100, temp_environment=20, [a,b] = [0,100]" << std::endl;
	for (int i=0;i<hvals.size();++i)
	{
		double h = hvals[i];
		std::cout << std::endl << "With h of " << h << ":" << std::endl;
		printResultsTable(explicitEuler(newtonCooling, y0, a, b, h));
	}
}
```
Output from the lines above:
```c++
Demonstrating newton's cooling law.
y0=100, temp_environment=20, [a,b] = [0,100]

With h of 10:
0.000 100.000
10.000 44.000
...
90.000 20.002
100.000 20.000

With h of 5.000:
0.000 100.000
5.000 72.000
...
95.000 20.022
100.000 20.014

With h of 2.000:
0.000 100.000
2.000 88.800
...
98.000 20.049
100.000 20.042
```
Output abridged for sake of brevity. To see full output, run explicitEulerTest.cpp (in directory with source for explicitEuler.hpp). Observe that accuracy of the approximation increases with a smaller h value.


**Implementation/Code:** The following is the code for explicitEuler(F,y0,a,b,h)
```c++
timesAndValues explicitEuler (double F(double, double), double y0, double a, double b, double h)
{
	timesAndValues r;
	r.a = a;
	r.b = b;
	double y = y0;
	for (double t=a; t<=b; t+=h)
	{
		r.time.push_back(t);
		r.value.push_back(y);
		y += h * F(t,y);
	}
	return r;
}
```
**Last Modified:** March/2018
