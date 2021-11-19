#include "processor.hpp"

Processor::Processor(size_t maxOfQueueSize_) { maxOfQueueSize = maxOfQueueSize_; }

void Processor::processRequest()
{
    if (currentNumberOfRequestsInQueue == 0)
    {
        return;
    }
}

void Processor::getRequest()
{
    if (currentNumberOfRequestsInQueue != maxOfQueueSize)
    {
        currentNumberOfRequestsInQueue++;

        if (currentNumberOfRequestsInQueue > detectedMaxOfRequestsInQueue)
        {
            detectedMaxOfRequestsInQueue = currentNumberOfRequestsInQueue;
        }
    }
}
