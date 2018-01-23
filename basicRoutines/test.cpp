#include <iostream>
#include "error.h"

int main (void)
{
	const double PI=3.141592653589793238462643;
	double x = 3.14; 
	std::cout << "Absolute error in a 3 digit approximation of PI is " << absoluteError(PI,x) << "\n";
	std::cout << "Relative error in a 3 digit approximation of PI is " << relativeError(PI,x) << "\n";
}