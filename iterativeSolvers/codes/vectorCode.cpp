#include "vectorCode.h"
#include <cmath>
#include <iostream>

typedef std::vector<double> Vector;

double vectorNormL1 (Vector v)
{
	double sum = 0.0;
	for (int i=0; i<v.size(); i++)
		sum+=std::abs(v[i]);
	return sum;
}

double vectorNormL2 (Vector v)
{
	double sum_of_squares = 0.0;
	for (int i=0; i<v.size(); i++)
		sum_of_squares+=v[i]*v[i];
	return sqrt(sum_of_squares);
}

double vectorNormLInf (Vector v)
{
	double maxElement = v[0];
	for(int i=1; i<v.size(); i++)
		if (v[i]>maxElement)
			maxElement=v[i];
	return maxElement;
}

Vector vectorDiff (Vector u, Vector v)
{
	int n = u.size();

	Vector diff (n, 0);
	for(int i=0;i<n;i++)
		diff[i] = v[i]-u[i];
	return diff;
}

Vector vectorScale (Vector v, double s)
{
	int n = v.size();

	Vector u (n, 0);
	for(int i=0;i<n;i++)
		u[i] = v[i]*s;
	return u;
}

double vectorErrorL1 (Vector u, Vector v)
{
	auto err = vectorDiff(u,v);
	return vectorNormL1(err);
}

double vectorErrorL2 (Vector u, Vector v)
{
	auto err = vectorDiff(u,v);
	return vectorNormL2(err);
}

double vectorErrorLInf (Vector u, Vector v)
{
	auto err = vectorDiff(u,v);
	return vectorNormLInf(err);
}

double dotProduct (Vector u, Vector v)
{
	double sum = 0;
	for (int i=0;i<u.size();++i)
		sum += u[i]*v[i];
	return sum;
}

void printVector (Vector v)
{
	if (v.size() == 0)
		return;

	std::cout << "[" << v[0];
	for (int i=1; i<v.size(); i++)
		std::cout << ", " << v[i];
	std::cout << "]" << std::endl;
}