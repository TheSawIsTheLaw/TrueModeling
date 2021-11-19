#include <random>

double equalDistributionRandomValue(double aParameter, double bParameter)
{
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(aParameter, bParameter);
    return distribution(generator);
}

double gaussDistributionRandomValue(double muParameter, double sigmaParameter)
{
    static thread_local std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(muParameter, sigmaParameter);
    return distribution(generator);
}
