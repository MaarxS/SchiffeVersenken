#include "CppRandom.hpp"

int Random::getRandomNumberBetween(int lower, int upper){
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}
