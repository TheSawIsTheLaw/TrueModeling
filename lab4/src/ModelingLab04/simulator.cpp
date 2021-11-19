#include "simulator.hpp"

Simulator::Simulator() {}

Simulator::Simulator(Processor processor_, RequestsGenerator requestGenerator_)
{
    processor = processor_;
    requestGenerator = requestGenerator_;
}

QPair<double, double> Simulator::simulateUsingDeltaTMethod(size_t numberOfRequests)
{
    double timeOfGenerationOfRequest = requestGenerator.getNextTimeOfRequestGenerated();
    double timeOfProcessing =
        timeOfGenerationOfRequest + processor.getNextTimeOfRequestProcessed();

    // Можно попробовать уменьшить deltaT
    for (double currentTime = 0; processor.numberOfProcessedRequests < numberOfRequests;
         currentTime += 1e-2)
    {
        if (timeOfGenerationOfRequest <= currentTime)
        {
            processor.getRequest();
            timeOfProcessing += requestGenerator.getNextTimeOfRequestGenerated();
        }

        if (timeOfProcessing <= currentTime)
        {
            processor.processRequest();
            (processor.currentNumberOfRequestsInQueue > 0)
                ? timeOfProcessing += processor.getNextTimeOfRequestProcessed()
                : timeOfProcessing = timeOfGenerationOfRequest +
                             processor.getNextTimeOfRequestProcessed();
        }
    }

    return QPair<double, double>(processor.numberOfReturnedRequests, processor.detectedMaxOfRequestsInQueue);
}

QPair<double, double> Simulator::simulateUsingEventMethod(size_t numberOfRequests)
{
    double timeOfGenerationOfRequest = requestGenerator.getNextTimeOfRequestGenerated();
    double timeOfProcessing = timeOfGenerationOfRequest + processor.getNextTimeOfRequestProcessed();

    while (processor.numberOfProcessedRequests < numberOfRequests)
    {
        if (timeOfGenerationOfRequest <= timeOfProcessing)
        {
            processor.getRequest();
            timeOfGenerationOfRequest += requestGenerator.getNextTimeOfRequestGenerated();
        }

        if (timeOfGenerationOfRequest >= timeOfProcessing)
        {
            processor.processRequest();
            (processor.currentNumberOfRequestsInQueue > 0)
                ? timeOfProcessing += processor.getNextTimeOfRequestProcessed()
                : timeOfProcessing = timeOfGenerationOfRequest +
                                     processor.getNextTimeOfRequestProcessed();
        }
    }

    return QPair<double, double>(processor.numberOfReturnedRequests, processor.detectedMaxOfRequestsInQueue);
}
