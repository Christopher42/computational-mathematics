**Routine Name:** runSimpleTest

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "ivpSolver.hpp"

**Description/Purpose:** Tests accuracy of IVP methods on simple exponential equation.

**Input:**
vector of IVP solver methods and vector containing the names of functions, in same order.

**Output:**
No return, will print computed values for each method (including analytic solution) for several input variable.

**Usage/Example:**

```c++
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#include "ivpSolver.hpp"

typedef std::function<timesAndValues (std::function<double(double,double)>, double, double, double, double)> solverFunction;
int main (void)
{
	std::vector<solverFunction> methods = {explicitEuler,itteratedRK2,itteratedRK4,adams34};
	std::vector<std::string> names = {"explicitEuler","Itterated RK2","Itterated RK4","Adams34 predictor-corrector"};
	runSimpleTest(methods, names);
}
```
Output from the lines above:
```c++
Testing solvers on "u'=lambda*u"
lambda = 1, y0 = 0.1
  exact
    0 0.1
    0.1 0.110517
    0.2 0.12214
    0.3 0.134986
    0.4 0.149182
    0.5 0.164872
    0.6 0.182212
    0.7 0.201375
    0.8 0.222554
    0.9 0.24596
    1 0.271828
  explicitEuler
    0 0.1
    0.1 0.1
    0.2 0.11
    0.3 0.13
    0.4 0.16
    0.5 0.2
    0.6 0.25
    0.7 0.31
    0.8 0.38
    0.9 0.46
    1 0.55
  Itterated RK2
    0 0.1
    0.1 0.1105
    0.2 0.122103
    0.3 0.134923
    0.4 0.14909
    0.5 0.164745
    0.6 0.182043
    0.7 0.201157
    0.8 0.222279
    0.9 0.245618
    1 0.271408
  Itterated RK4
    0 0.1
    0.1 0.110517
    0.2 0.12214
    0.3 0.134986
    0.4 0.149182
    0.5 0.164872
    0.6 0.182212
    0.7 0.201375
    0.8 0.222554
    0.9 0.24596
    1 0.271828
  Adams34 predictor-corrector
    0 0.1
    0.1 0.110517
    0.2 0.12214
    0.3 0.134986
    0.4 0.149182
    0.5 0.149182
    0.6 0.164872
    0.7 0.182211
    0.8 0.201373
    0.9 0.222551
    1 0.245957
```
For the sake of brevity, only output from first test case (of 9 test cases) is included. Full table of output values included in [Analysis of methods](https://christopher42.github.io/computational-mathematics/differentialEquationSolvers/ivp/analysis).


**Implementation/Code:** The following is the code for runSimpleTest(methods, names). Dependent methods included.
```c++
typedef std::function<timesAndValues (std::function<double(double,double)>, double, double, double, double)> solverFunction;

// u' = lambda * u, u(0) = u0
double simpleTest (double t, double lambda, double u0)
{
	return u0 * exp(lambda*t);
}

void printExact(double lambda, double y0, double a, double b, double h)
{
	std::cout << "  exact" << std::endl;
	for (double x=a; x<=b; x+=h)
	{
		std::cout << "    " << x << " " << simpleTest(x,lambda,y0) << std::endl;
	}
}

double simpleTestF (double u, double lambda)
{
	return lambda*u;
}

void runSimpleTest (std::vector<solverFunction> methods, std::vector<std::string> names)
{
	std::cout << "Testing solvers on \"u'=lambda*u\"" << std::endl;
	double a=0;
	double b=1;
	double h=(b-a)/10;
	std::vector<double> lambdaVals = {-1,1,100};
	std::vector<double> initialVals = {.1,.01,.001};
	lambdaVals = {1};
	initialVals = {.1};
	for (int i=0;i<lambdaVals.size();++i)
	{
		double lambda = lambdaVals[i];
		for (int j=0;j<initialVals.size();++j)
		{
			double y0 = initialVals[j];
			std::cout << "lambda = " << lambda << ", y0 = " << y0 << std::endl;
			printExact(lambda,y0,a,b,h);
			for (int k=0;k<methods.size();++k)
			{
				auto method = methods[k];
				std::cout << "  " << names[k] << std::endl;
				auto f = [lambda](double u, double t)->double{return simpleTestF(u,lambda);};
				timesAndValues results = method(f,y0,a,b,h);
				printResultsTable(results);
			}
		}
	}
}
```
**Last Modified:** April/2018
