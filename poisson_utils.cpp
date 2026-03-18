#define NUMBER_OF_EXPERIMENTS 10000
#include "distribution_generator.hpp"

#include<vector>
#include<unordered_map>
#include<iostream>
#include<cmath>
#include<numbers>

#include <boost/math/distributions/chi_squared.hpp>

std::unordered_map<int, int> get_observed_data(int average_rate){
    std::vector<distribution> distributions;
    std::unordered_map<int, int> frequency_of_occurences;

    for(int i = 0; i < NUMBER_OF_EXPERIMENTS; i++){
        distribution dis;
        dis.generate_distribution(average_rate);

        frequency_of_occurences[dis.N]++;

        distributions.push_back(dis);
    }

    return frequency_of_occurences;
}

double poisson_pmf(double lambda, int k) {
    double log_pmf = k * std::log(lambda) - lambda - std::lgamma(k + 1);
    return std::exp(log_pmf);
}

double get_critical_value(int degrees_of_freedom, double alpha){
    boost::math::chi_squared_distribution<double> dist(degrees_of_freedom);
    double critical_value = boost::math::quantile(dist, 1.0 - alpha);
    return critical_value;
}

bool measure_gof(std::unordered_map<int, int> &observed, int lambda) {
    double total_chi_sq = 0.0;
    double bin_obs = 0.0;
    double bin_exp = 0.0;
    int num_bins = 0;

    for (int k = 0; k < (lambda * 3 + 10); ++k) {
        double expected = NUMBER_OF_EXPERIMENTS * poisson_pmf(lambda, k);
        
        bin_exp += expected;
        bin_obs += observed[k];

        // Rule of 5: Only calculate once the bin is large enough
        if(bin_exp >= 5.0) {
            total_chi_sq += std::pow(bin_obs - bin_exp, 2) / bin_exp;
            
            bin_exp = 0.0;
            bin_obs = 0.0;
            num_bins++;
        }
    }

    if (bin_exp > 0.0 && num_bins > 0) {
        total_chi_sq += std::pow(bin_obs - bin_exp, 2) / bin_exp;
        num_bins++;
    }

    int degrees_of_freedom = num_bins - 1;

    if(degrees_of_freedom < 1){
        std::cout << "Error: Not enough bins for a valid test." << std::endl;
        return false;
    }

    double critical_value = get_critical_value(degrees_of_freedom, 0.05);

    // std::cout << "Chi-squared statistic: " << total_chi_sq << std::endl;
    // std::cout << "Critical value (0.95): " << critical_value << std::endl;

    if(total_chi_sq <= critical_value){
        // std::cout << "PASS: It is a Poisson Distribution" << std::endl;
        return true;
    }else{
        // std::cout << "FAIL: Not a Poisson Distribution" << std::endl;
        return false;
    }
}