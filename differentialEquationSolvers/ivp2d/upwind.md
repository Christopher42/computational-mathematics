**Routine Name:** upwind

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

**Implementation/Code:** The following is the code for upwind.
```c++
std::vector<double> upwind (double a, double t0, double t1, int tsteps, std::pair<std::vector<double>,std::vector<double>> mesh)
{
	std::vector<double> index = mesh.second;
	std::vector<double> oldVal = mesh.first;
	std::vector<double> newVal;
	int n = index.size();
	double h = (index[n-1]-index[0])/n; //h=dx
	double k = (t1-t0)/tsteps; //k=dt

	for (int j=0;j<=tsteps;++j)
	{
		//for periodic
		newVal.push_back(oldVal[0] - a*k/h*(oldVal[0]-oldVal[n-1]));
		//for derelict boundary conditions (use one of the two)
		// newVal.push_back(oldVal[0]);

		//fill out rest of vector
		for (int i=1;i<index.size();++i)
		{
			newVal.push_back(oldVal[i] - a*k/h*(oldVal[i]-oldVal[i-1]));
		}
		oldVal = newVal;
		newVal = std::vector<double>(0);
	}

	return oldVal;
}
```
**Last Modified:** May/2018
