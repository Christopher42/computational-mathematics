**Routine Name:** rk4

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "ivpSolver.hpp"

**Description/Purpose:** Take a single timestep in an initial value problem with second order accuracy, using runge-kutta 4. Function itteratedRK4 will itterate by time steps to some t_n.

**Input:**
Takes as input: function F: R^2->R, initial value y0, interval bounds a < b, and step size h.

**Output:**
Returns estimated value after next step.

**Usage/Example:**
example usage in itteratedRK2.
```c++
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
```
For example output, see simpleTest().


**Implementation/Code:** The following is the code for rk4 (f, y, t, dt);
```c++
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
```
**Last Modified:** April/2018
