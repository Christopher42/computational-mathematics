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

double explicitEuler (std::function<double(double,double)> F, double y0, double a, double b, double h)
{
	double iter = (b-a)/h;
	double y = y0;
	double t;
	for (int i=0;i<iter;++i)
	{
		t = a + h*i;
		y = y + h * F(y,t);
	}
	return y;
}

double implicitEuler (std::function<double(double,double)> F, double y0, double a, double b, double h)
{
	double iter = (b-a)/h;
	double y=y0;
	double t;
	// u^n+1 = u^n + h*f(u^n+1)
	for (int i=1;i<iter+1;++i)
	{
		t = a + h*i;
		double ynew=y;
		for (int i=0;i<100;++i)
		{
			ynew = y + h*F(ynew,t);
		}
		y=ynew;
	}
	return y;
}

double itteratedRK2 (std::function<double(double,double)> F, double y0, double a, double b, double h)
{
	double iter = (b-a)/h;
	double y = y0;
	double t;
	for (int i=0;i<iter;++i)
	{
		t = a + h*i;
		y = rk2(F,y,t,h);
	}
	return y;
}

double itteratedRK4 (std::function<double(double,double)> F, double y0, double a, double b, double h)
{
	double iter = (b-a)/h;
	double y = y0;
	double t;
	for (int i=0;i<iter;++i)
	{
		t = a + h*i;
		y = rk4(F,y,t,h);
	}
	return y;
}

double adams34 (std::function<double(double,double)> F, double y0, double a, double b, double h)
{	
	double iter = (b-a)/h;
	double t;
	double t0 = a;
	double t1 = a+h;
	double t2 = a+h*2;
	double t3 = a+h*3;
	double u0 = y0;
	double u1 = rk4(F,u0,t0,h);
	double u2 = rk4(F,u1,t1,h);
	double u3 = rk4(F,u2,t2,h);
	
	for (int i=4; i<iter+1; ++i)
	{
		t = a + h*i;
		double y = u3 + h/24 * (-9*F(u0,t0) + 37*F(u1,t1) - 59*F(u2,t2) + 55*F(u3,t3));
		double u4 = u3 + h/24*(F(u1,t1) - 5*F(u2,t2) + 19*F(u3,t3) + 9*F(y,t));
		u0=u1; u1=u2; u2=u3; u3=u4;
		t0=t1; t1=t2; t2=t3; t3=t;
	}
	return u3;
}
