#include <iostream>
#include <chrono>
#include <omp.h>
#include "parallelOperations.h"

int main()
{
	std::cout << "Max number of threads: " << omp_get_max_threads() << std::endl;

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