#include "simulator.hpp"

Simulator::Simulator() {}

Simulator::Simulator(Processor processor_, RequestsGenerator requestGenerator_)
{
    processor = processor_;
    requestGenerator = requestGenerator_;
}

QPair<double, double> Simulator::simulateUsingDeltaTMethod(size_t numberOfRequests)
{
    double timeOfGeneration = requestGenerator.getNextTimeOfRequestGenerated();
    double timeOfProcessing =
        timeOfGeneration + processor.getNextTimeOfRequestProcessed();

    size_t numberOfSentRequests = 0;
    for (double currentTime = 0; numberOfSentRequests < numberOfRequests;
         currentTime += 1e-3)
    {
        while (timeOfGeneration <= currentTime)
        {
            numberOfSentRequests++;
            processor.getRequest();

            timeOfGeneration += requestGenerator.getNextTimeOfRequestGenerated();
        }

        while (timeOfProcessing <= currentTime)
        {
            processor.processRequest();

            (processor.currentNumberOfRequestsInQueue > 0)
                ? timeOfProcessing += processor.getNextTimeOfRequestProcessed()
                : timeOfProcessing = timeOfGeneration +
                                     processor.getNextTimeOfRequestProcessed();
        }
    }

    while (processor.currentNumberOfRequestsInQueue > 0)
    {
        processor.processRequest();
    }

    return QPair<double, double>(
        processor.numberOfReturnedRequests, processor.detectedMaxOfRequestsInQueue);
}

QPair<double, double> Simulator::simulateUsingEventMethod(size_t numberOfRequests)
{
    double timeOfGeneration = requestGenerator.getNextTimeOfRequestGenerated();
    double timeOfProcessing =
        timeOfGeneration + processor.getNextTimeOfRequestProcessed();

    size_t numberOfSentRequests = 0;
    while (numberOfSentRequests < numberOfRequests)
    {
        while (timeOfGeneration <= timeOfProcessing)
        {
            numberOfSentRequests++;
            processor.getRequest();

            timeOfGeneration += requestGenerator.getNextTimeOfRequestGenerated();
        }

        while (timeOfGeneration >= timeOfProcessing)
        {
            processor.processRequest();
            (processor.currentNumberOfRequestsInQueue > 0)
                ? timeOfProcessing += processor.getNextTimeOfRequestProcessed()
                : timeOfProcessing = timeOfGeneration +
                                     processor.getNextTimeOfRequestProcessed();
        }
    }

    while (processor.currentNumberOfRequestsInQueue > 0)
    {
        processor.processRequest();
    }

    return QPair<double, double>(
        processor.numberOfReturnedRequests, processor.detectedMaxOfRequestsInQueue);
}
