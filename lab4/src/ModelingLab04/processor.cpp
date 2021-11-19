#include "processor.hpp"

Processor::Processor(double probabilityOfReturnToQueue_)
{
    probabilityOfReturnToQueue = probabilityOfReturnToQueue_;
}

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
