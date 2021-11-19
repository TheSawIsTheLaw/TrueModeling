#include "simulator.hpp"

Simulator::Simulator() {}

Simulator::Simulator(Processor processor_, RequestsGenerator requestGenerator_)
{
    processor = processor_;
    requestGenerator = requestGenerator_;
}

#include <QDebug>
QPair<double, double> Simulator::simulateUsingDeltaTMethod(size_t numberOfRequests)
{
    double timeOfGenerationOfRequest = requestGenerator.getNextTimeOfRequestGenerated();
    double timeOfProcessing =
        timeOfGenerationOfRequest + processor.getNextTimeOfRequestProcessed();

    size_t numberOfSentRequests = 0;
    // Можно попробовать уменьшить deltaT
    for (double currentTime = 0; numberOfSentRequests < numberOfRequests;
         currentTime += 1e-2)
    {
//        qDebug() << processor.numberOfProcessedRequests << numberOfRequests;
//        qDebug() << "Current time" << currentTime;
//        qDebug() << "Time of generation" << timeOfGenerationOfRequest;
//        qDebug() << "Time of processing" << timeOfProcessing;
        if (timeOfGenerationOfRequest <= currentTime)
        {
            numberOfSentRequests++;
            processor.getRequest();
            timeOfGenerationOfRequest += requestGenerator.getNextTimeOfRequestGenerated();
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

    size_t numberOfSentRequests = 0;
    while (numberOfSentRequests < numberOfRequests)
    {
        if (timeOfGenerationOfRequest <= timeOfProcessing)
        {
            numberOfSentRequests++;
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
