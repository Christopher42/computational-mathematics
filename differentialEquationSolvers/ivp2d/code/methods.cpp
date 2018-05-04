#include "methods.hpp"

//assuming function is periodic
std::pair<std::vector<double>,std::vector<double>> advection (double a, double b, int xsteps, std::function<double(double)> initial)
{
	std::vector<double> index;
	std::vector<double> val;
	for (int i=0; i<=xsteps; ++i)
	{
		double x = a + (b-a)*i/xsteps;
		index.push_back(x);
		val.push_back(initial(x));
	}
	return std::make_pair(val,index);
}

//assuming periodic
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

//assuming periodic
std::vector<double> laxWendroff (double a, double t0, double t1, int tsteps, std::pair<std::vector<double>,std::vector<double>> mesh)
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
			double x = oldVal[n-1];
			double y = oldVal[0];
			double z = oldVal[1];

			double next = y -(a*k/2/h)*(x-z) +(a*a*k*k/2/h/h)*(x-2*y+z);
			newVal.push_back(next);
		}
		//fill out rest of vector
		for (int i=1;i<index.size()-1;++i)
		{
			double x = oldVal[i-1];
			double y = oldVal[i];
			double z = oldVal[i+1];

			double next = y -(a*k/2/h)*(x-z) +(a*a*k*k/2/h/h)*(x-2*y+z);
			newVal.push_back(next);
		}
		//last value
		{
			double x = oldVal[n-2];
			double y = oldVal[n-1];
			double z = oldVal[0];

			double next = y -(a*k/2/h)*(x-z) +(a*a*k*k/2/h/h)*(x-2*y+z);
			newVal.push_back(next);
		}
		oldVal=newVal;
		newVal = std::vector<double>(0);
	}
	return oldVal;
}

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