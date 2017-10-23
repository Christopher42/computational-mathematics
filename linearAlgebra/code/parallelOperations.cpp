#include <cstdlib>
#include <ctime>
#include "parallelOperations.h"

Vector parallelMatrixVectorProduct(const Matrix &a, const Vector &v)
{
	int m = a.size();
	int n = a[0].size();
	int i,j;
	Vector sol(m,0);

	#pragma omp parallel for private(j)
	for (i=0;i<m;++i)
		for (j=0;j<n;++j)
			sol[i]+=a[i][j]*v[j];
	return sol;
}

Matrix parallelMatrixMatrixProduct(const Matrix &a, const Matrix &b)
{
	int n = a.size();
	int m = b.size();
	int r = b[0].size();
	int i,j,k;

	Matrix sol(n, Vector(r,0));

	#pragma omp parallel for private(j,k)
	for(i=0;i<n;++i)
		for(j=0;j<r;++j)
			for(k=0;k<m;++k)
				sol[i][j]+=a[i][k]*b[k][j];
	return sol;
}

Matrix randMatrix(int n, int m)
{
	std::srand(std::time(0));
	Matrix a (n, Vector(m));
	#pragma omp parallel for
	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j)
			a[i][j]=rand()%100;
	return a;
}

Vector randVector(int n)
{
	std::srand(std::time(0));
	Vector v(n);
	#pragma omp parallel for
	for (int i=0;i<n;++i)
		v[i]=rand()%100;
	return v;
}