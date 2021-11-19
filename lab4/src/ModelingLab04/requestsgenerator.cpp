#include "requestsgenerator.hpp"

RequestsGenerator::RequestsGenerator(double muParameter_, double sigmaParameter_)
{
    muParameter = muParameter_;
    sigmaParameter = sigmaParameter_;
}

double RequestsGenerator::getNextTimeOfRequestGenerated()
{
    return gaussDistributionRandomValue(muParameter, sigmaParameter);
}
