#include "modelingElements.hpp"

double equalDistributionRandomValue(double aParameter, double bParameter)
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(aParameter, bParameter);
    return distribution(generator);
}

double gaussDistributionRandomValue(double muParameter, double sigmaParameter)
{
    static std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(muParameter, sigmaParameter);
    return distribution(generator);
}

Processor::Processor() {}

Processor::Processor(
    double probabilityOfReturnToQueue_, double muParameter_, double sigmaParameter_)
{
    probabilityOfReturnToQueue = probabilityOfReturnToQueue_;
    muParameter = muParameter_;
    sigmaParameter = sigmaParameter_;
}

#include <QDebug>
void Processor::processRequest()
{
    if (currentNumberOfRequestsInQueue == 0)
    {
        return;
    }

    currentNumberOfRequestsInQueue--;
    if (equalDistributionRandomValue(0, 1) < probabilityOfReturnToQueue)
    {
        numberOfReturnedRequests++;
        getRequest();
    }
}

void Processor::getRequest()
{
    currentNumberOfRequestsInQueue++;

    if (currentNumberOfRequestsInQueue > detectedMaxOfRequestsInQueue)
    {
        detectedMaxOfRequestsInQueue = currentNumberOfRequestsInQueue;
    }
}

double Processor::getNextTimeOfRequestProcessed()
{
    return gaussDistributionRandomValue(muParameter, sigmaParameter);
}

RequestsGenerator::RequestsGenerator() {}

RequestsGenerator::RequestsGenerator(double aParameter_, double bParameter_)
{
    aParameter = aParameter_;
    bParameter = bParameter_;
}

double RequestsGenerator::getNextTimeOfRequestGenerated()
{
    return equalDistributionRandomValue(aParameter, bParameter);
}

