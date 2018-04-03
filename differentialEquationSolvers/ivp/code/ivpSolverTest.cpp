#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#include "ivpSolver.hpp"

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

int main (void)
{
	std::vector<solverFunction> methods = {explicitEuler,itteratedRK2,itteratedRK4,adams34};
	std::vector<std::string> names = {"explicitEuler","Itterated RK2","Itterated RK4","Adams34 predictor-corrector"};
	runSimpleTest(methods, names);
}