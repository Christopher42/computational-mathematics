#include <iostream>
#include "tridiag.h"

double f (double x)
{
	return sin(x*3.14159);
}

double k (double x)
{
	return 1;
}

void printVector (std::vector<double> x)
{
	std::cout << '[' << x[0];
	for (int i=1;i<x.size();++i)
		std::cout << ", " << x[i];
	std::cout << ']' << std::endl;
}

void printElliptic(TridiagSys A)
{
	std::cout << "Upper diagonal: [";
	printVector(A.upper);
	std::cout << "Main diagonal: [";
	printVector(A.main);
	std::cout << "Lower diagonal: [";
	printVector(A.lower);
	std::cout << "Mesh: [";
	printVector(A.mesh);
	std::cout << "B: [";
	printVector(A.b);
}

void testSimpleElliptic(int m)
{
	double a = 0;
	double b = 1;
	double ua = 2.5;
	double ub = 5.0;
	TridiagSys A = initSimpleElliptic(m, a, b, f, ua, ub);
	TridiagSys ts = A;
	std::vector<double> v = thomasAlg(ts);
	printVector(v);
	ts=A;
	v = jacobiTridiag(ts);
	printVector(v);
	ts=A;
	luTridiag(ts);
	v = evalLUTridiag(ts, ts.b);
	printVector(v);
	// printElliptic(A);
}

void testElliptic(int m)
{
	double a = 0;
	double b = 1;
	double ua = 2.5;
	double ub = 5.0;
	TridiagSys A = initElliptic(m, a, b, f, k, ua, ub);
	TridiagSys ts = A;
	std::vector<double> v = thomasAlg(ts);
	printVector(v);
	ts=A;
	v = jacobiTridiag(ts);
	printVector(v);
	ts=A;
	luTridiag(ts);
	v = evalLUTridiag(ts, ts.b);
	printVector(v);
	printElliptic(A);
}

int main (void)
{
	for (int i=1;i<4;++i)
	{
		std::cout << "With mesh of " << i << std::endl;
		testSimpleElliptic(i);
		// testElliptic(i);
		std::cout << std::endl;
	}

	return 0;
}