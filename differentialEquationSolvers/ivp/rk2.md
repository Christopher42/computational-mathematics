**Routine Name:** rk2

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "ivpSolver.hpp"

**Description/Purpose:** Take a single timestep in an initial value problem with second order accuracy, using runge-kutta 2. Function itteratedRK2 will itterate by time steps to some t_n.

**Input:**
Takes as input: function F: R^2->R, initial value y0, interval bounds a < b, and step size h.

**Output:**
Returns estimated value after next step.

**Usage/Example:**
example usage in itteratedRK2.
```c++
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
```
For example output, see simpleTest().


**Implementation/Code:** The following is the code for rk2 (f, y, t, dt);
```c++
double rk2 (std::function<double(double,double)> f, double y, double t, double dt)
{
	double Y1 = y + .5*dt*f(y,t);
	double u_new = y + dt*f(Y1,t+dt/2);
	return u_new;
}
```
**Last Modified:** April/2018
