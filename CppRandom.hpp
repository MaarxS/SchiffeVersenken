#ifndef CPP_RANDOM_DHBW
#define CPP_RANDOM_DHBW
#include <random>
#include <iostream>
#include <ctime>
class Random {
    //Will be used to obtain a seed for the random number engine
    std::random_device rd;
        //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen;

    public:
    Random(): gen(rd()) {}
    int GetRandomNumberBetween(int lower, int upper);
};

#endif