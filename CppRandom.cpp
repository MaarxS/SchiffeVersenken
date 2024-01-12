#include "CppRandom.hpp"

int Random::GetRandomNumberBetween(int lower, int upper){
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}
