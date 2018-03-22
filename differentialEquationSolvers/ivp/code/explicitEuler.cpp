#include <iostream>
#include <iomanip>
#include "explicitEuler.hpp"

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

void printResultsTable (timesAndValues in)
{
	for (int i=0; i<in.time.size(); ++i)
	{
		std::cout << std::fixed << std::setprecision(3) << in.time[i] << " " << in.value[i] << std::endl;
	}
}