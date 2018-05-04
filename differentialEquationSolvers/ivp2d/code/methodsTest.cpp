#include "methods.hpp"
#include <cmath>
#include <iostream>

typedef std::pair<std::vector<double>,std::vector<double>> pair;

typedef std::function<std::vector<double>(double, double, double, int, pair)> methodSig;

double f (double t)
{
	if (t>0 and t<2)
		return sin(2.0*M_PI*t);
	else
		return 0;
}

void test (double constant, double t0, double t1, double tsteps, std::pair<std::vector<double>,std::vector<double>> mesh, methodSig method)
{
	auto result = method(constant, t0, t1, tsteps, mesh);
	for (int i=10; i<20; ++i)
		std::cout << result[i] << '\t';
	std::cout << std::endl;
}

int main (void)
{
	double a=0;
	double b=2;
	int xsteps = 20;
	auto mesh = advection(a,b,xsteps,f);

	for (int i=10; i<20; ++i)
		std::cout << mesh.second[i] << '\t';
	std::cout << std::endl;

	double constant = .1;
	double t0 = 0;
	double t1 = 1;
	double tsteps = 100;
	test(constant,t0,t1,tsteps,mesh,upwind);
	test(constant,t0,t1,tsteps,mesh,laxWendroff);
	test(constant,t0,t1,tsteps,mesh,beamWarming);
	return 0;
}