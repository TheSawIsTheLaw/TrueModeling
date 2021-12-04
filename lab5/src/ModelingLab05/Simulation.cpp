#include "Simulation.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <limits>
#include <vector>

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
    : numberOfGeneratedRequests(0)
    , returnReceiver(nullptr)
    , generator(generator_)
    , receivers()
    , timeOfNextEvent(0.0)
    {
    }

    virtual ~RequestGenerator() {}

    void subscribeReceiver(Processor *receiver) { receivers.push_back(receiver); }

    double getNextTime() const { return generator(); }

    Processor *sendRequest()
    {
        numberOfGeneratedRequests++;
        if (receivers.size() == 3)
        {
            Processor *receiver = receivers[0];

            double currentSum = 0;
            double chooseRandom = getUniformReal(0, 1);
            // Бросаем точку на прямую, разделённую на отрезки, суммирование -
            // рассмотрение отдельного отрезка Господи, до чего я дошёл в своём познании,
            // Вы бы только знали
            for (size_t i = 0; i < pValuesToSendTo.size(); i++)
            {
                currentSum += pValuesToSendTo[i];
                if (chooseRandom < currentSum)
                {
                    receiver = receivers[i];
                    break;
                }
            }

            if (receiver->getRequest())
            {
                qDebug() << "Receive";
                return receiver;
            }
            qDebug() << "Not";
            return nullptr;
        }
        else
        {
            for (auto &&receiver : receivers)
            {
                if (receiver->getRequest())
                {
                    return receiver;
                }
            }
        }
        if (receivers.size() == 0)
            qDebug() << "It's null";
        return nullptr;
    }

    Processor *returnRequestToSubscriber()
    {
        if (!returnReceiver)
        {
            qDebug() << "Return receiver is not defined!";
            return nullptr;
        }
        returnReceiver->getRequest();
        return returnReceiver;
    }

public:
    int numberOfGeneratedRequests;
    Processor *returnReceiver;

private:
    Generator generator;
    std::vector<Processor *> receivers;

public:
    double timeOfNextEvent;
    std::vector<double> pValuesToSendTo;
};

class RequestProcessor : public RequestGenerator, public Processor
{
public:
    using Generator = RequestGenerator::Generator;

    RequestProcessor(
        Generator generator, int maxOfQueue_ = 0, double probabilityOfReturn_ = 0.0)
    : RequestGenerator(generator)
    , Processor()
    , numberOfRequestsInQueue(0)
    , numberOfProcessedRequests(0)
    , numberOfSkippedRequests(0)
    , maxOfQueue(maxOfQueue_)
    , numberOfReturns(0)
    , probabilityOfReturn(probabilityOfReturn_)
    {
    }

    ~RequestProcessor() override {}

    void process()
    {
        if (numberOfRequestsInQueue > 0)
        {
            numberOfProcessedRequests++;
            numberOfRequestsInQueue--;
            sendRequest();

            if (getUniformReal(0, 1) < probabilityOfReturn)
            {
                numberOfReturns++;
                returnRequestToSubscriber();
            }
        }
        timeOfNextEvent = numberOfRequestsInQueue ? currentTime + getNextTime() : 0.0;
    }

    bool getRequest() override
    {
        const auto cond = maxOfQueue == 0 || numberOfRequestsInQueue < maxOfQueue;
        if (cond)
        {
            numberOfRequestsInQueue++;
            timeOfNextEvent = numberOfRequestsInQueue ? currentTime + getNextTime() : 0.0;
        }
        else
        {
            numberOfSkippedRequests++;
        }
        return cond;
    }

public:
    int numberOfRequestsInQueue;
    int numberOfProcessedRequests;
    int numberOfSkippedRequests;

private:
    int maxOfQueue;
    int numberOfReturns;
    double probabilityOfReturn;
};

Results doSimulate(const SimulationParameters &parameters)
{
    RequestGenerator generatorOfClients([=]() {
        return getUniformReal(parameters.client.timeOfCome - parameters.client.timeDelta,
            parameters.client.timeOfCome + parameters.client.timeDelta);
    });

    RequestProcessor terminal([=]() {
        return getUniformReal(
            parameters.terminal.timeOfService - parameters.terminal.timeDelta,
            parameters.terminal.timeOfService + parameters.terminal.timeDelta);
    });
    std::vector<double> pValuesToSendTo = {parameters.client.probForSendWindow,
        parameters.client.probForGetWindow, parameters.client.probForMoneytalksWindow};
    terminal.pValuesToSendTo = pValuesToSendTo;
    RequestProcessor sendWindow(
        [=]() {
            return getUniformReal(
                parameters.sendWindow.timeOfService - parameters.sendWindow.timeDelta,
                parameters.sendWindow.timeOfService + parameters.sendWindow.timeDelta);
        },
        parameters.sendWindow.maxQueueSize,
        parameters.client.probabilityOfReturnToMainQueue);
    RequestProcessor getWindow(
        [=]() {
            return getUniformReal(
                parameters.getWindow.timeOfService - parameters.getWindow.timeDelta,
                parameters.getWindow.timeOfService + parameters.getWindow.timeDelta);
        },
        parameters.getWindow.maxQueueSize,
        parameters.client.probabilityOfReturnToMainQueue);
    RequestProcessor moneytalksWindow(
        [=]() {
            return getUniformReal(parameters.moneytalksWindow.timeOfService -
                                      parameters.moneytalksWindow.timeDelta,
                parameters.moneytalksWindow.timeOfService +
                    parameters.moneytalksWindow.timeDelta);
        },
        parameters.moneytalksWindow.maxQueueSize,
        parameters.client.probabilityOfReturnToMainQueue);

    generatorOfClients.subscribeReceiver(&terminal);
    terminal.subscribeReceiver(&sendWindow);
    terminal.subscribeReceiver(&getWindow);
    terminal.subscribeReceiver(&moneytalksWindow);
    sendWindow.returnReceiver = &terminal;
    getWindow.returnReceiver = &terminal;
    moneytalksWindow.returnReceiver = &terminal;

    const std::array<RequestGenerator *, 5> devices{
        &generatorOfClients, &terminal, &sendWindow, &getWindow, &moneytalksWindow};

    generatorOfClients.timeOfNextEvent = generatorOfClients.getNextTime();
    terminal.timeOfNextEvent =
        generatorOfClients.timeOfNextEvent + terminal.getNextTime();
    while (generatorOfClients.numberOfGeneratedRequests < parameters.client.amount)
    {
        qDebug() << "In terminal: " << terminal.numberOfRequestsInQueue;
        qDebug() << "In first window: " << sendWindow.numberOfRequestsInQueue;
        qDebug() << "In second window: " << getWindow.numberOfRequestsInQueue;
        qDebug() << "In third window: " << moneytalksWindow.numberOfRequestsInQueue;
        currentTime = generatorOfClients.timeOfNextEvent;
        for (auto &&device : devices)
        {
            if (device->timeOfNextEvent != 0 && device->timeOfNextEvent < currentTime)
            {
                currentTime = device->timeOfNextEvent;
            }
        }

        for (auto &&device : devices)
        {
            if (currentTime == device->timeOfNextEvent)
            {
                RequestProcessor *processor = dynamic_cast<RequestProcessor *>(device);
                if (processor)
                {
                    processor->process();
                }
                else
                {
                    generatorOfClients.sendRequest();
                    generatorOfClients.timeOfNextEvent =
                        currentTime + generatorOfClients.getNextTime();
                }
            }
        }
    }

    while (terminal.numberOfRequestsInQueue > 0 ||
           sendWindow.numberOfRequestsInQueue > 0 ||
           getWindow.numberOfRequestsInQueue > 0 ||
           moneytalksWindow.numberOfRequestsInQueue > 0)
    {
        qDebug() << "In terminal: " << terminal.numberOfRequestsInQueue;
        qDebug() << "In first window: " << sendWindow.numberOfRequestsInQueue;
        qDebug() << "In second window: " << getWindow.numberOfRequestsInQueue;
        qDebug() << "In third window: " << moneytalksWindow.numberOfRequestsInQueue;
        currentTime = std::numeric_limits<double>::max();
        for (size_t i = 1; i < devices.size(); i++)
        {
            if (devices[i]->timeOfNextEvent != 0 &&
                devices[i]->timeOfNextEvent < currentTime)
            {
                currentTime = devices[i]->timeOfNextEvent;
            }
        }

        for (size_t i = 1; i < devices.size(); i++)
        {
            if (currentTime == devices[i]->timeOfNextEvent)
            {
                dynamic_cast<RequestProcessor *>(devices[i])->process();
            }
        }
    }

    const auto res = [](const RequestProcessor &processor) {
        const auto numberOfSkippedRequests = processor.numberOfSkippedRequests;
        const auto numberOfProcessedRequests = processor.numberOfProcessedRequests;
        const auto probabilityOfRequestToBeSkipped =
            static_cast<double>(numberOfSkippedRequests) /
            (numberOfSkippedRequests + numberOfProcessedRequests);
        return Results::Element{numberOfSkippedRequests, probabilityOfRequestToBeSkipped};
    };

    return {res(terminal), res(sendWindow), res(getWindow), res(moneytalksWindow)};
}
