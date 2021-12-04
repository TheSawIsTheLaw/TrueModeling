#pragma once

#include <random>

int uniform_int(int a, int b) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

double uniform_real(double a, double b) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(a, b);
    return distribution(generator);
}

double normal(double mu, double sigma) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(mu, sigma);
    return distribution(generator);
}