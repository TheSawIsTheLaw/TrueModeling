#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "distributions.cpp"
#include <iostream>

class Processor
{
public:
    Processor();
    Processor(double probabilityOfReturnToQueue_);

    void getRequest();
    void processRequest();

    double getNextTimeOfRequestProcessed();

    size_t detectedMaxOfRequestsInQueue = 0;
    size_t numberOfProcessedRequests = 0;

    size_t currentNumberOfRequestsInQueue = 0;
    size_t numberOfReturnedRequests = 0;

    double probabilityOfReturnToQueue;

private:
    double muParameter = 0;
    double sigmaParameter = 1;
};

#endif // PROCESSOR_HPP
