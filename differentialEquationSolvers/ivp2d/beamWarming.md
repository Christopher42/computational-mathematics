**Routine Name:** laxWendroff

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** methods.hpp

**Description/Purpose:** uses upwinding technique to solve linear advection equation.

**Input:**
double a - constant of advection
double t0, t1 - time range
int tsteps - number of steps to iterate over time range
`std::pair<std::vector<double>std::vector<double>> mesh` - mesh object output by advection() method

**Output:**
`std::vector<double>` containing computed function values for end time.

**Usage/Example:**
see methodsTest.cpp for usage.

**Implementation/Code:** The following is the code for beamWarming
```c++
//assuming periodic
std::vector<double> beamWarming (double a, double t0, double t1, int tsteps, std::pair<std::vector<double>,std::vector<double>> mesh)
{
	std::vector<double> index = mesh.second;
	std::vector<double> oldVal = mesh.first;
	std::vector<double> newVal;
	int n = index.size();
	double h = (index[n-1]-index[0])/n; //h=dx
	double k = (t1-t0)/tsteps; //k=dt

	for (int j=0;j<=tsteps;++j)
	{
		//first value
		{
			double x = oldVal[n-2];
			double y = oldVal[n-1];
			double z = oldVal[0];

			double next = z - (a*k/2/h)*(3*z-4*y+x) + (a*a*k*k/2/h/h)*(z-2*y+x);
			newVal.push_back(next);
		}
		//second value
		{
			double x = oldVal[n-1];
			double y = oldVal[0];
			double z = oldVal[1];

			double next = z - (a*k/2/h)*(3*z-4*y+x) + (a*a*k*k/2/h/h)*(z-2*y+x);
			newVal.push_back(next);
		}
		//fill out rest of vector
		for (int i=2;i<index.size()-1;++i)
		{
			double x = oldVal[i-2];
			double y = oldVal[i-1];
			double z = oldVal[i];

			double next = z - (a*k/2/h)*(3*z-4*y+x) + (a*a*k*k/2/h/h)*(z-2*y+x);
			newVal.push_back(next);
		}
		oldVal=newVal;
		newVal = std::vector<double>(0);
	}
	return oldVal;
}
```
**Last Modified:** May/2018
