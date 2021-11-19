#ifndef MODELINGELEMENTS_H
#define MODELINGELEMENTS_H

#include <iostream>
#include <random>

class RequestsGenerator
{
public:
    RequestsGenerator();
    RequestsGenerator(double aParameter_, double bParameter_);

    double getNextTimeOfRequestGenerated();

private:
    double aParameter = 0;
    double bParameter = 1;
};

class Processor
{
public:
    Processor();
    Processor(
        double probabilityOfReturnToQueue_, double muParameter_, double sigmaParameter_);

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

#endif // MODELINGELEMENTS_H
