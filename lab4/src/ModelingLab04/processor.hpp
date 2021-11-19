#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "distributions.cpp"
#include <iostream>

class Processor
{
public:
    Processor(double probabilityOfReturnToQueue_);

    void getRequest();
    void processRequest();

    size_t detectedMaxOfRequestsInQueue = 0;

    size_t currentNumberOfRequestsInQueue = 0;
    size_t numberOfReturnedRequests = 0;

    double probabilityOfReturnToQueue;
};

#endif // PROCESSOR_HPP
