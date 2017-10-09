#include "matrix.h"
#include <cmath>
#include <iostream>

double matrixNormL1 (Matrix m)
{
	double maxColumnSum = 0;
	for (int j=0;j<m[0].size();j++)
	{
		double sum = 0;
		for (int i=0;i<m.size();i++)
			sum+= std::abs(m[i][j]);
		if (sum > maxColumnSum)
			maxColumnSum = sum;
	}
	return maxColumnSum;
}


double matrixNormLInf (Matrix m)
{
	double maxRowSum = 0;
	for (int i=0;i<m.size();i++)
	{
		double sum = 0;
		for (int j=0;j<m[0].size();j++)
			sum+= std::abs(m[i][j]);
		if (sum > maxRowSum)
			maxRowSum = sum;
	}
	return maxRowSum;
}

void printMatrix (Matrix m)
{
	for (int i=0;i<m.size();i++)
	{
		std::cout << ((i==0) ? '[' : ' ');
		std::cout << "[" << m[i][0];
		for (int j=1; j<m[i].size(); j++)
			std::cout << "," << m[i][j];
		std::cout << "]" << ((i==m.size()-1) ? ']' : ',') << std::endl;
	}
}

Matrix identityMatrix(int n)
{
	Matrix ident(n, Vector(n,0));
	for (int i=0;i<n;++i)
		ident[i][i] = 1;
	return ident;
}

Matrix matrixAdd(Matrix a, Matrix b)
{
	int n = a.size();
	int m = a[0].size();
	Matrix sol (m, Vector(n,0));

	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j)
			sol[i][j] = a[i][j] + b[i][j];

	return sol;
}

Matrix matrixSub(Matrix a, Matrix b)
{
	int n = a.size();
	int m = a[0].size();
	Matrix sol (m, Vector(n,0));

	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j)
			sol[i][j] = a[i][j] - b[i][j];

	return sol;
}

Matrix matrixScale(Matrix a, double s)
{
	Matrix sol = a;

	for (int i=0;i<a.size();++i)
		for (int j=0;j<a[0].size();j++)
			sol[i][j]*= s;

	return sol;
}

Vector matrixVectorProduct(Matrix a, Vector v)
{
	int m = a.size();
	int n = a[0].size();
	Vector sol(m,0);

	for (int i=0;i<m;++i)
		for (int j=0;j<n;++j)
			sol[i]+=a[i][j]*v[j];
	return sol;
}

Matrix matrixMatrixProduct(Matrix a, Matrix b)
{
	int n = a.size();
	int m = b.size();
	int r = b[0].size();

	Matrix sol(n, Vector(r,0));

	for(int i=0;i<n;++i)
		for(int j=0;j<r;++j)
			for(int k=0;k<m;++k)
				sol[i][j]+=a[i][k]*b[k][j];
	return sol;
}