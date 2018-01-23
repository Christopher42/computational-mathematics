#include <iostream>
#include "machineEpsilon.h"

int main (void)
{
	std::cout << "single precision is " << machineEpsilonSingle() << " digits.\n";
	std::cout << "double precision is " << machineEpsilonDouble() << " digits.\n";
}