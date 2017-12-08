#include <iostream>
#include <random>
#include "vectorCode.h"
#include "matrix.h"
#include "iterativeSolvers.h"

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
    
    int n;
    std::cout << "N=";
    std::cin >> n;
	Matrix A = randPositiveDefMatrix(n,dis,gen);
	Vector b = randVect(n,dis,gen);
	Vector x(n,.5);
	Vector x_0;

	// int n = 3;
	// Matrix A{{25,1,1},{1,25,1},{1,1,25}};
	// Vector b{1004,1004,1004};
	// Vector x(n,.5);
	// Vector x_0;
	
    // int n = 2;
	// Matrix A{{12,7},{3,4}};
	// Vector b(n,.5);
	// Vector x(n,.5);
	// Vector x_0;

	//Jacobi test
	x_0 = x;
	std::cout << "Jacobi converges in ";
	std::cout << jacobi(A,b,x_0);
	std::cout << " iterations.\n";
	printMatrix(x_0);

	//GS test
	x_0 = x;
	std::cout << "Gauss-Seidel converges in ";
	std::cout << gaussSeidel(A,b,x_0);
	std::cout << " iterations.\n";
	std::cout << "err = " << vectorNormL1(vectorDiff(matrixVectorProduct(A,x_0),b)) << std::endl;

	//Steepest Descent
	x_0 = x;
	std::cout << "Steepest Descent converges in ";
	std::cout << steepestDescent(A,b,x_0);
	std::cout << " iterations.\n";
	std::cout << "err = " << vectorNormL1(vectorDiff(matrixVectorProduct(A,x_0),b)) << std::endl;

	//Conjugate Gradient
	x_0 = x;
	std::cout << "Conjugate Gradient converges in ";
	std::cout << conjugateGradient(A,b,x_0);
	std::cout << " iterations.\n";
	std::cout << "err = " << vectorNormL1(vectorDiff(matrixVectorProduct(A,x_0),b)) << std::endl;

	//power method
	x_0 = b;
	double lambda = powerMethod(A,x_0);
	std::cout << "Largest eigenvalue (by power method) is ";
	std::cout << lambda << std::endl;

	//inverse power method
	x_0 = b;
	lambda = inversePowerMethod(A,x_0);
	std::cout << "Smallest eigenvalue (by inverse power method) is ";
	std::cout << lambda << std::endl;


	return 0;
}