#ifndef _METHODS_HPP
#define _METHODS_HPP


#include <functional>
#include <utility>
#include <vector>

std::pair<std::vector<double>,std::vector<double>> advection (double a, double b, int xsteps, std::function<double(double)> initial);

std::vector<double> upwind (double a, double t0, double t1, int tsteps, std::pair<std::vector<double>,std::vector<double>> mesh);

std::vector<double> laxWendroff (double a, double t0, double t1, int tsteps, std::pair<std::vector<double>,std::vector<double>> mesh);

std::vector<double> beamWarming (double a, double t0, double t1, int tsteps, std::pair<std::vector<double>,std::vector<double>> mesh);

#endif