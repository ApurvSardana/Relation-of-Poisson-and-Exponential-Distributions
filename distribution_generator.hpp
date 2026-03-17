#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include<iostream>
#include<vector>
#include<random>

class distribution{
    public:
    int N; //Number of events occured in simulated process
    std::vector<int> data; //Time intervals between events

    distribution(){
        N = 0;
        data.clear();
    }

    void generate_distribution(int average_rate){
        /*
            Let us simulate a process:
            An event occurs at random times.
            The time intervals between any 2 consecutive events is a variable
            that follows the Exponential Probability Distribution.
            Its formula is as follows:

            P(x) = lambda * e ^ (-lambda * x)
            (lambda is average rate : 1 / (average time interval))

            Read it is as:
            P(x) is the probability that the length of the time interval is x

            Now, what is the probability that the length of the time interval <= x?
            It is the sum of all the probabilities P(L), such that 0 <= L <= x,
            which using integration, comes out to be:

            CDF(x) = 1 - e ^ (-lambda * x)
            (CDF stands for Cumulative Density Function)

            Now, we can rearrange the above equation, and get:

            x = -ln(1 - CDF(x)) / lambda 
            (This is important)

            This means, for a given value of CDF(x), we have to wait x units of time
            (x is unique, I promise)

            Now, What we do is -> Generate a random number u
            This u is CDF(x)
            Since, we know that for a Cumulative Probability to be u, how much time needs we need to wait
            (using the above formula). We can increment our time counter. And count one occurence of the event

            Do this until the time counter hits 1 unit

            This will give us the number of events happening in 1 unit of time, with average rate = lambda

        */

        //For generating random probabilities
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> get_random_number(0.0, 1.0);

        double time = 0.0;

        while(time < 1.0){
            double cdf = get_random_number(gen);
            double wait_time = -log(1.0 - cdf) / average_rate;

            time += wait_time;

            //Only count an event which occurs before 1 unit time
            if(time < 1.0){
                N++;
                data.push_back(wait_time);
            }
        }
    }
};

#endif