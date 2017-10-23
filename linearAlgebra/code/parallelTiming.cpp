#include <iostream>
#include <chrono>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include "matrix.h"

Vector parallelMatrixVectorProduct(Matrix a, Vector v)
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

Matrix parallelMatrixMatrixProduct(Matrix a, Matrix b)
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
	Matrix a (n, Vector(m));
	#pragma omp parallel for
	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j)
			a[i][j]=rand()%100;
	return a;
}

Vector randVector(int n)
{
	Vector v(n);
	#pragma omp parallel for
	for (int i=0;i<n;++i)
		v[i]=rand()%100;
	return v;
}

int main()
{
	std::cout << "Max number of threads: " << omp_get_max_threads() << std::endl;

	// std::vector<int> N = {500};
	std::vector<int> N = {1,2,4,10,21,46,100};
	std::vector<double> matrixMatrixTime(N.size());
	std::vector<double> matrixVectorTime(N.size());

	for (int i=0;i<N.size();++i)
	{
		double mtime = 0;
		double vtime = 0;
		for (int r=0;r<3;++r)
		{
			int n = N[i];
			Matrix A = randMatrix(n,n);
			Matrix B = randMatrix(n,n);
			Vector V = randVector(n);

			auto start = std::chrono::steady_clock::now();
			Matrix c = parallelMatrixMatrixProduct(A,B);
			auto end = std::chrono::steady_clock::now();
			auto diff = end - start;
			mtime += (double)(std::chrono::duration <double, std::milli> (diff).count());

			start = std::chrono::steady_clock::now();
			Vector v = parallelMatrixVectorProduct(A,V);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			vtime += (double)(std::chrono::duration <double, std::milli> (diff).count());
		}
		matrixMatrixTime[i] = mtime/3;
		matrixVectorTime[i] = vtime/3;
	}

	std::cout << "n\tmatrixVectorTime\n";
	for (int i=0;i<N.size();++i)
		std::cout << N[i] << "\t" << matrixVectorTime[i] << std::endl;

	std::cout << "n\tmatrixMatrixTime\n";
	for (int i=0;i<N.size();++i)
		std::cout << N[i] << "\t" << matrixMatrixTime[i] << std::endl;
}