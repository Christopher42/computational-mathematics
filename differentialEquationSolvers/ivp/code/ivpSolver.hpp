#pragma once

#include <vector>
#include <functional>

struct timesAndValues
{
	double a,b;
	std::vector<double> time;
	std::vector<double> value;
};

double rk2 (std::function<double(double,double)> f, double y, double t, double dt);
double rk4 (std::function<double(double,double)> f, double y, double t, double dt);

double explicitEuler (std::function<double(double,double)> F, double y0, double a, double b, double h);
double itteratedRK2 (std::function<double(double,double)> F, double y0, double a, double b, double h);
double itteratedRK4 (std::function<double(double,double)> F, double y0, double a, double b, double h);
double adams34 (std::function<double(double,double)> F, double y0, double a, double b, double h);
double implicitEuler (std::function<double(double,double)> F, double y0, double a, double b, double h);