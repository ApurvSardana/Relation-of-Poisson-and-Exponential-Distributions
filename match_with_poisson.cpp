#include "poisson_utils.hpp"
#include <iostream>

int main(){
    int average_rate;
    std::cin >> average_rate;

    auto observed = get_observed_data(average_rate);
    std::cout << (measure_gof(observed, average_rate) ? "PASS" : "FAIL") << std::endl;
}