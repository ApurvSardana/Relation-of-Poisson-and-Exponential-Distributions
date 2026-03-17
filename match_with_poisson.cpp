#define NUMBER_OF_EXPERIMENTS 1000
#include<distribution_generator.hpp>

#include<vector>
#include<unordered_map>

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

int main(){
    int average_rate;
    std::cout << "Enter average number of events in the interval: ";
    std::cin >> average_rate;

    std::unordered_map<int, int> observed = get_observed_data(average_rate);

    //Calculate Chi-Squared -> I'll do it tomorrow
    return 0;
}