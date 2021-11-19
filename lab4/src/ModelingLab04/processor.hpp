#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <iostream>

class Processor
{
public:
    Processor(size_t maxOfQueueSize_);

    void getRequest();
    void processRequest();

    size_t maxOfQueueSize = 0;
    size_t detectedMaxOfRequestsInQueue = 0;

    size_t currentNumberOfRequestsInQueue = 0;
    size_t numberOfReturnedRequests = 0;

};

#endif // PROCESSOR_HPP
