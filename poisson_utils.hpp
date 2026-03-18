#ifndef POISSON_UTILS_HPP
#define POISSON_UTILS_HPP

#include <unordered_map>

std::unordered_map<int, int> get_observed_data(int average_rate);
bool measure_gof(std::unordered_map<int, int> &observed, int lambda);
double poisson_pmf(double lambda, int k);
double get_critical_value(int degrees_of_freedom, double alpha);

#endif