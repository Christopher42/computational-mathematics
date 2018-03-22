#ifndef tridiag_h
#define tridiag_h

#include <vector>
#include <cmath>

struct TridiagSys {
int n;
std::vector<double> main;
std::vector<double> upper;
std::vector<double> lower;
std::vector<double> mesh;
std::vector<double> b;
};

TridiagSys initSimpleElliptic(int m, double a, double b, double (*f)(double), double u_a, double u_b);
TridiagSys initElliptic(int m, double a, double b, double (*f)(double), double (*k)(double), double u_a, double u_b);

std::vector<double> thomasAlg(TridiagSys& A);
void luTridiag(TridiagSys& A);
std::vector<double> evalLUTridiag(const TridiagSys& A, const std::vector<double>& b);
std::vector<double> jacobiTridiag( TridiagSys& A, int maxIter=40, double tol=pow(10.0,-8.0));

std::vector<std::vector<double>> convertToSquare (TridiagSys);

#endif