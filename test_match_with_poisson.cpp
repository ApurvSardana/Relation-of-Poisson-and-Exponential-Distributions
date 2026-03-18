#define MAX_LAMBDA 500
#include "poisson_utils.hpp"
#include <iostream>

int main() {
    int pass_count;
    for (int lambda = 1; lambda <= MAX_LAMBDA; lambda++) {
        std::cout << lambda << " : ";
        auto observed = get_observed_data(lambda);
        
        if(measure_gof(observed, lambda)){
            pass_count++;
            std::cout << "PASS" << std::endl;
        }else{
            std::cout << "FAIL" << std::endl;
        }
    }

    std::cout << "PASS PERCENTAGE : " << ((double)pass_count / (double)MAX_LAMBDA) * 100.0 << std::endl;
    return 0;
}