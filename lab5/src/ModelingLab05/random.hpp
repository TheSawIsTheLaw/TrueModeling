#pragma once

#include <random>

int getUniformReal(int a, int b) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

double getUniformInt(double a, double b) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(a, b);
    return distribution(generator);
}
