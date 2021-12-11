#pragma once

#include <random>

double getUniformReal(double aParameter, double bParameter) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(aParameter, bParameter);
    return distribution(generator);
}

int getUniformInt(int aParameter, int bParameter) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(aParameter, bParameter);
    return distribution(generator);
}
