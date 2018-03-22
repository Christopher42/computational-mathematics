#include "explicitEuler.hpp"

#include <iostream>

double newtonCooling (double time, double temp)
{
	//temp is a function of time, but time is not used directly
	return -0.07*(temp-20);
}

int main (void)
{
	double y0=100;
	double a=0;
	double b=100;
	std::vector<double> hvals = {10,5,2};
	std::cout << "Demonstrating newton's cooling law." << std::endl;
	std::cout << "y0=100, temp_environment=20, [a,b] = [0,100]" << std::endl;
	for (int i=0;i<hvals.size();++i)
	{
		double h = hvals[i];
		std::cout << std::endl << "With h of " << h << ":" << std::endl;
		printResultsTable(explicitEuler(newtonCooling, y0, a, b, h));
	}
}