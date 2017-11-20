#include <iostream>
#include <random>
#include <omp.h>
#include <chrono>
#include <ctime>
#include "iterativeSolversParallel.h"
#include "iterativeSolvers.h"
#include "vectorCode.h"
#include "matrix.h"

Matrix randPositiveDefMatrix(int n, std::uniform_real_distribution<>dis, std::mt19937 gen)
{
    Matrix A (n,Vector(n,0));
    //Set Upper
    for (int i=0;i<n;++i)
    	for (int j=i;j<n;++j)
    		A[i][j]=dis(gen);
    //mirror to Lower
    for (int i=0;i<n;++i)
    	for(int j=0;j<i;++j)
    		A[i][j] = A[j][i];
    //add n to Diag
    for (int i=0;i<n;++i)
    	A[i][i]+=n;

    return A;
}

Vector randVect(int n, std::uniform_real_distribution<> dis, std::mt19937 gen)
{
	Vector v(n,0);
	for (int i=0;i<n;++i)
		v[i]=dis(gen)+1;
	return v;
}

int main (void)
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
	std::cout << "Max number of threads: " << omp_get_max_threads() << std::endl;

	// std::vector<int> N = {500};
	std::vector<int> N = {1,2,4,10,21,46,100,215,464,1000,2154};
	std::vector<double> jacobiTime(N.size());
	std::vector<double> steepestDescentTime(N.size());
	std::vector<double> conjugateGradientTime(N.size());
	std::vector<double> powerMethodTime(N.size());
	std::vector<double> inversePowerMethodTime(N.size());
	std::vector<double> p_jacobiTime(N.size());
	std::vector<double> p_steepestDescentTime(N.size());
	std::vector<double> p_conjugateGradientTime(N.size());
	std::vector<double> p_powerMethodTime(N.size());
	std::vector<double> p_inversePowerMethodTime(N.size());

	for (int i=0;i<N.size();++i)
	{
		double j_time = 0;
		double s_time = 0;
		double c_time = 0;
		double p_time = 0;
		double ip_time = 0;
		double p_j_time = 0;
		double p_s_time = 0;
		double p_c_time = 0;
		double p_p_time = 0;
		double p_ip_time = 0;
		for (int r=0;r<7;++r)
		{
			//initialization
			int n = N[i];
			Matrix A = randPositiveDefMatrix(n,dis,gen);
			Vector b = randVect(n,dis,gen);
			Vector x(n,.5);
			Vector x_0;

			//jacobi
			x_0=x;
			auto start = std::chrono::steady_clock::now();
			jacobi(A,b,x_0);
			auto end = std::chrono::steady_clock::now();
			auto diff = end - start;
			j_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			x_0=x;
			start = std::chrono::steady_clock::now();
			p_jacobi(A,b,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			p_j_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			//steepest descent
			x_0=x;
			start = std::chrono::steady_clock::now();
			steepestDescent(A,b,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			s_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			x_0=x;
			start = std::chrono::steady_clock::now();
			p_steepestDescent(A,b,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			p_s_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			//conjugate gradient
			x_0=x;
			start = std::chrono::steady_clock::now();
			conjugateGradient(A,b,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			c_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			x_0=x;
			start = std::chrono::steady_clock::now();
			p_conjugateGradient(A,b,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			p_c_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			//power method
			x_0 = b;
			start = std::chrono::steady_clock::now();
			powerMethod(A,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			p_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			x_0 = b;
			start = std::chrono::steady_clock::now();
			p_powerMethod(A,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			p_p_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			//inverse power method
			x_0 = b;
			start = std::chrono::steady_clock::now();
			inversePowerMethod(A,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			ip_time += (double)(std::chrono::duration <double, std::milli> (diff).count());

			x_0 = b;
			start = std::chrono::steady_clock::now();
			p_inversePowerMethod(A,x_0);
			end = std::chrono::steady_clock::now();
			diff = end - start;
			p_ip_time += (double)(std::chrono::duration <double, std::milli> (diff).count());


		}
		jacobiTime[i] = j_time/7;
		steepestDescentTime[i] = s_time/7;
		conjugateGradientTime[i] = c_time/7;
		powerMethodTime[i] = p_time/7;
		inversePowerMethodTime[i] = ip_time/7;
		p_jacobiTime[i] = p_j_time/7;
		p_steepestDescentTime[i] = p_s_time/7;
		p_conjugateGradientTime[i] = p_c_time/7;
		p_powerMethodTime[i] = p_p_time/7;
		p_inversePowerMethodTime[i] = p_ip_time/7;
	}
	std::cout << "Jacobi time\n";
	std::cout << "n\tSerial\tParallel\n";
	for (int i=0;i<N.size();++i)
		std::cout << N[i] << "\t" << jacobiTime[i] << "\t" << p_jacobiTime[i] << std::endl;

	std::cout << "Steepest Descent time\n";
	std::cout << "n\tSerial\tParallel\n";
	for (int i=0;i<N.size();++i)
		std::cout << N[i] << "\t" << steepestDescentTime[i] << "\t" << p_steepestDescentTime[i] << std::endl;

	std::cout << "Conjugate Gradient Time\n";
	std::cout << "n\tSerial\tParallel\n";
	for (int i=0;i<N.size();++i)
		std::cout << N[i] << "\t" << conjugateGradientTime[i] << "\t" << p_conjugateGradientTime[i] << std::endl;

	std::cout << "Power Method Time\n";
	std::cout << "n\tSerial\tParallel\n";
	for (int i=0;i<N.size();++i)
		std::cout << N[i] << "\t" << powerMethodTime[i] << "\t" << p_powerMethodTime[i] << std::endl;

	std::cout << "Inverse Power Method Time\n";
	std::cout << "n\tSerial\tParallel\n";
	for (int i=0;i<N.size();++i)
		std::cout << N[i] << "\t" << inversePowerMethodTime[i] << "\t" << p_inversePowerMethodTime[i] << std::endl;

	return 0;
}