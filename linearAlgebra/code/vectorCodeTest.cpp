#include "vectorCode.h"
#include <iostream>

int main (void)
{
	Vector a = {1,2,3};
	Vector a_bar = {1.1, 1.9, 3.2};
	std::cout << "Let A denote the vector ";
	printVector(a);
	std::cout << std::endl;
	std::cout << "The l-norms of the vector A are as follows:" << std::endl;
	std::cout << "l1 norm: " << vectorNormL1(a) << std::endl;
	std::cout << "l2 norm: " << vectorNormL2(a) << std::endl;
	std::cout << "l-infinity norm: " << vectorNormLInf(a) << std::endl;

	std::cout << "Now, let A* denote an approximation of A, given as ";
	printVector(a_bar);
	std::cout << std::endl;
	std::cout << "The vector error of A* relative to A is given in the l-norms as follows:" << std::endl;
	std::cout << "l1 error: " << vectorErrorL1(a,a_bar) << std::endl;
	std::cout << "l2 error: " << vectorErrorL2(a,a_bar) << std::endl;
	std::cout << "l-infinity error: " << vectorErrorLInf(a,a_bar) << std::endl;

	std::cout << "The dot product of A and A* is " << dotProduct(a,a_bar) << std::endl;
}