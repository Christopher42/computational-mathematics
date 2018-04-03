#include <iostream>
#include <iomanip>
#include <cmath>

#include "ivpSolver.hpp"


double rk2 (std::function<double(double,double)> f, double y, double t, double dt)
{
	double Y1 = y + .5*dt*f(y,t);
	double u_new = y + dt*f(Y1,t+dt/2);
	return u_new;
}

double rk4 (std::function<double(double,double)> f, double y, double t, double dt)
{
	double t1 = t + dt/2;
	double t2 = t + dt;
	double Y1 = y;
	double Y2 = y + .5*dt*f(Y1,t);
	double Y3 = y + .5*dt*f(Y2,t1);
	double Y4 = y + dt*f(Y3,t1);
	double u_new = y + (dt/6)*(f(Y1,t)+2*f(Y2,t1)+2*f(Y3,t1)+f(Y4,t2));
	return u_new;
}

timesAndValues explicitEuler (std::function<double(double,double)> F, double y0, double a, double b, double h)
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

timesAndValues itteratedRK2 (std::function<double(double,double)> F, double y0, double a, double b, double h)
{
	timesAndValues r;
	r.a = a;
	r.b = b;
	double y = y0;
	for (double t=a; t<=b; t+=h)
	{
		r.time.push_back(t);
		r.value.push_back(y);
		y = rk2(F,y,t,h);
	}
	return r;
}

timesAndValues itteratedRK4 (std::function<double(double,double)> F, double y0, double a, double b, double h)
{
	timesAndValues r;
	r.a = a;
	r.b = b;
	double y = y0;
	for (double t=a; t<=b; t+=h)
	{
		r.time.push_back(t);
		r.value.push_back(y);
		y = rk4(F,y,t,h);
	}
	return r;
}

timesAndValues adams34 (std::function<double(double,double)> F, double y0, double a, double b, double h)
{
	timesAndValues r;
	r.a = a;
	r.b = b;
	double y = y0;
	double t=a;
	for (int i=0;i<4;++i)
	{
		r.time.push_back(t);
		r.value.push_back(y);
		y = rk4(F,y,t,h);
		t+=h;
	}

	double u0 = r.value[0];
	double u1 = r.value[1];
	double u2 = r.value[2];
	double u3 = r.value[3];
	double t0 = r.time[0];
	double t1 = r.time[1];
	double t2 = r.time[2];
	double t3 = r.time[3];

	for (t; t<=b; t+=h)
	{
		r.time.push_back(t);
		r.value.push_back(y);
		double u4 = u3 + h/24 * (-9*F(u0,t0) + 37*F(u1,t1) - 59*F(u2,t2) + 55*F(u3,t3));
		y = u3 + h/24*(F(u1,t1) - 5*F(u2,t2) + 19*F(u3,t3) + 9*F(u4,t));
		u0 = u1; u1=u2; u2=u3; u3=u4;
		t0 = t1; t1=t2; t2=t3; t3=t;
	}
	return r;
}

void printResultsTable (timesAndValues in)
{
	for (int i=0; i<in.time.size(); ++i)
	{
		std::cout << "    " << in.time[i] << " " << in.value[i] << std::endl;
	}
}