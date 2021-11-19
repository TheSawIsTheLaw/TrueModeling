#include "processor.hpp"

Processor::Processor(double probabilityOfReturnToQueue_, double muParameter_, double sigmaParameter_)
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
