#include "modelingElements.hpp"

double equalDistributionRandomValue(double aParameter, double bParameter)
{
    static thread_local std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(aParameter, bParameter);
    return distribution(generator);
}

double gaussDistributionRandomValue(double muParameter, double sigmaParameter)
{
    static thread_local std::default_random_engine generator;
    static std::normal_distribution<double> distribution(muParameter, sigmaParameter);
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

void Processor::processRequest()
{
    if (currentNumberOfRequestsInQueue == 0)
    {
        return;
    }

    currentNumberOfRequestsInQueue--;
    numberOfProcessedRequests++;
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

