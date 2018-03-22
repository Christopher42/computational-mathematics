#pragma once

#include <vector>

struct timesAndValues
{
	double a,b;
	std::vector<double> time;
	std::vector<double> value;
};

//y'=f(y,t)
timesAndValues explicitEuler (double F(double, double), double y0, double a, double b, double h);
void printResultsTable (timesAndValues in);