#include "Simulation.hpp"

#include <QtDebug>

#include "random.hpp"

double currentTime;

class Processor
{
public:
    virtual ~Processor() {}

    virtual bool getRequest() = 0;
};

class RequestGenerator
{
public:
    using Generator = std::function<double()>;

    RequestGenerator(Generator generator_)
    {
        numberOfGeneratedRequests = 0;
        generator = generator_;
        receivers = std::vector<Processor *>();
        timeOfNextEvent = 0;
    }

    virtual ~RequestGenerator() {}

    void subscribeReceiver(Processor *receiver) { receivers.push_back(receiver); }

    double getNextTime() { return generator(); }

    Processor *sendRequest()
    {
        numberOfGeneratedRequests++;
        for (auto &&receiver : receivers)
        {
            if (receiver->getRequest())
                return receiver;
        }

        return nullptr;
    }

public:
    int numberOfGeneratedRequests;

private:
    Generator generator;
    std::vector<Processor *> receivers;

public:
    double timeOfNextEvent;
};

class RequestProcessor : public RequestGenerator, public Processor
{
public:
    using Generator = RequestGenerator::Generator;

    RequestProcessor(
        Generator generator, int maxOfQueue_ = 0)
    : RequestGenerator(generator), Processor()
    {
        numberOfRequestsInQueue = 0;
        numberOfProcessedRequests = 0;
        maxOfQueue = maxOfQueue_;
    }

    ~RequestProcessor() override {}

    void process()
    {
        if (numberOfRequestsInQueue > 0)
        {
            numberOfProcessedRequests++;
            numberOfRequestsInQueue--;
            sendRequest();
        }

        timeOfNextEvent = numberOfRequestsInQueue ? currentTime + getNextTime() : 0.0;
    }

    bool getRequest() override
    {
        if (maxOfQueue == 0 || numberOfRequestsInQueue < maxOfQueue)
        {
            numberOfRequestsInQueue++;
            if (timeOfNextEvent == 0)
            {
                timeOfNextEvent = currentTime + getNextTime();
            }

            return true;
        }
        else
        {
            return false;
        }
    }

public:
    int numberOfRequestsInQueue;
    int numberOfProcessedRequests;

private:
    int maxOfQueue;
};

Results doSimulate(const SimulationParameters &parameters)
{
    RequestGenerator generatorOfClients([=]() {
        return getUniformReal(parameters.client.timeOfCome - parameters.client.timeDelta,
            parameters.client.timeOfCome + parameters.client.timeDelta);
    });

    RequestProcessor operator1(
        [=]() {
            return getUniformReal(
                parameters.operator1.timeOfService - parameters.operator1.timeDelta,
                parameters.operator1.timeOfService + parameters.operator1.timeDelta);
        },
        1);
    RequestProcessor operator2(
        [=]() {
            return getUniformReal(
                parameters.operator2.timeOfService - parameters.operator2.timeDelta,
                parameters.operator2.timeOfService + parameters.operator2.timeDelta);
        },
        1);
    RequestProcessor operator3(
        [=]() {
            return getUniformReal(
                parameters.operator3.timeOfService - parameters.operator3.timeDelta,
                parameters.operator3.timeOfService + parameters.operator3.timeDelta);
        },
        1);

    RequestProcessor computer1([=]() { return parameters.computer1.timeOfService; });
    RequestProcessor computer2([=]() { return parameters.computer2.timeOfService; });

    generatorOfClients.subscribeReceiver(&operator1);
    generatorOfClients.subscribeReceiver(&operator2);
    generatorOfClients.subscribeReceiver(&operator3);

    operator1.subscribeReceiver(&computer1);
    operator2.subscribeReceiver(&computer1);
    operator3.subscribeReceiver(&computer2);

    std::array<RequestGenerator *, 6> schemeElements{
        &generatorOfClients, &operator1, &operator2, &operator3, &computer1, &computer2};

    int numberOfDenials = 0;
    generatorOfClients.timeOfNextEvent = generatorOfClients.getNextTime();

    while (computer1.numberOfProcessedRequests + computer2.numberOfProcessedRequests <
           parameters.client.amountOfProccessedNeeded)
    {
        qDebug() << "At time: " << currentTime;
        qDebug() << "In operator1: " << operator1.numberOfRequestsInQueue << operator1.timeOfNextEvent;
        qDebug() << "In operator2: " << operator2.numberOfRequestsInQueue << operator2.timeOfNextEvent;
        qDebug() << "In operator3: " << operator3.numberOfRequestsInQueue << operator3.timeOfNextEvent;
        qDebug() << "In computer1: " << computer1.numberOfRequestsInQueue
                 << computer1.numberOfProcessedRequests << computer1.timeOfNextEvent;
        qDebug() << "In computer2: " << computer2.numberOfRequestsInQueue
                 << computer2.numberOfProcessedRequests << computer2.timeOfNextEvent;
        currentTime = generatorOfClients.timeOfNextEvent;
        for (auto &&element : schemeElements)
        {
            if (element->timeOfNextEvent != 0 && element->timeOfNextEvent < currentTime)
            {
                currentTime = element->timeOfNextEvent;
            }
        }

        for (auto &&element : schemeElements)
        {
            if (currentTime == element->timeOfNextEvent)
            {
                RequestProcessor *processor = dynamic_cast<RequestProcessor *>(element);
                if (processor)
                {
                    processor->process();
                }
                else
                {
                    Processor *catchProcessor = generatorOfClients.sendRequest();
                    if (!catchProcessor)
                    {
                        numberOfDenials++;
                    }

                    generatorOfClients.timeOfNextEvent =
                        currentTime + generatorOfClients.getNextTime();
                }
            }
        }
    }

    return {numberOfDenials,
        static_cast<double>(numberOfDenials) /
            (static_cast<double>(numberOfDenials) + operator1.numberOfProcessedRequests +
                operator2.numberOfProcessedRequests +
                operator3.numberOfProcessedRequests)};
}
