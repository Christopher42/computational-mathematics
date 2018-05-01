#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#include "ivpSolver.hpp"

typedef std::function<double (std::function<double(double,double)>, double, double, double, double)> solverFunction;

// u' = lambda * u, u(0) = u0
double simpleTest (double t, double lambda, double u0)
{
	return u0 * exp(lambda*t);
}

void printExact(double lambda, double y0, double a, double b, double h)
{
	double x=a;
	while (x<=b)
		x+=h;
	std::cout << simpleTest(x,lambda,y0);
}

void printLabels(std::vector<std::string> names)
{
	std::cout << "exact";
	for (int i=0;i<names.size();++i)
	{
		std::cout << '\t' << names[i];
	} 
	std::cout << std::endl;
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
	double h=.001;
	std::vector<double> lambdaVals = {-1,1,100};
	std::vector<double> initialVals = {.1,.01,.001};
	// lambdaVals = {1};
	// initialVals = {.1};

	//calculate values at all points
	for (int i=0;i<lambdaVals.size();++i)
	{
		double lambda = lambdaVals[i];
		std::cout << "lambda = " << lambda << std::endl;
		std::cout << "y0\t";
		printLabels(names);
		for (int j=0;j<initialVals.size();++j)
		{
			double y0 = initialVals[j];
			std::cout << y0 << '\t';
			printExact(lambda,y0,a,b,h);
			for (int k=0;k<methods.size();++k)
			{
				auto method = methods[k];
				auto f = [lambda](double u, double t)->double{return simpleTestF(u,lambda);};
				double result = method(f,y0,a,b,h);
				std::cout << '\t' << result;
			}
			std::cout << std::endl;
		}
	}
}

double testFunc (double u, double t){
	double l = -2100;
	return l*(u-cos(t))-sin(t);
}

void test (std::vector<solverFunction> methods, std::vector<std::string> names)
{
	std::cout << "Testing solvers on \"u'=-sin(t)\"" << std::endl;
	double a=0.0;
	double b=2.0;
	double h=.000001;
	double y0=1.0;

	//calculate values at all points
	printLabels(names);
	std::cout << cos(2.0);
	for (int k=0;k<methods.size();++k)
	{
		auto method = methods[k];
		auto f = testFunc;
		double result = method(f,y0,a,b,h);
		std::cout << '\t' << result;
	}
	std::cout << std::endl;
}

int main (void)
{
	std::vector<solverFunction> methods = {explicitEuler,implicitEuler,itteratedRK2,itteratedRK4,adams34};
	std::vector<std::string> names = {"explicitEuler","implicitEuler","Itterated RK2","Itterated RK4","Adams34 predictor-corrector"};
	test(methods, names);
}