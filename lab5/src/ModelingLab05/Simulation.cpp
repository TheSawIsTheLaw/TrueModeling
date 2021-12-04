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

    virtual bool receive_request() = 0;
};

class RequestGenerator
{
public:
    using Generator = std::function<double()>;

    RequestGenerator(Generator generator)
    : generator_(generator)
    , receivers_()
    , return_receiver_(nullptr)
    , n_generated_requests_(0)
    , next_event_time(0.0)
    {
    }

    virtual ~RequestGenerator() {}

    int n_generated_requests() const { return n_generated_requests_; }

    void add_receiver(Processor *receiver) { receivers_.push_back(receiver); }

    void set_return_receiver(Processor *return_receiver)
    {
        return_receiver_ = return_receiver;
    }

    double generate_time() const { return generator_(); }

    Processor *emit_request()
    {
        ++n_generated_requests_;
        double sendToCondition = getUniformInt(0, 1);

        Processor *receiverToReceiveRequest = nullptr;
        if (receivers_.size() == 3)
        {
            for (size_t i = 0; i < receivers_.size(); i++)
            {
                qDebug() << receivers_.size();
                qDebug() << pReturns[i];
                if (pReturns[i] < sendToCondition)
                {
                    receiverToReceiveRequest = receivers_[i];
                }
            }
        }
        else
        {
            receiverToReceiveRequest = receivers_[0];
        }

        if (receiverToReceiveRequest)
        {
            receiverToReceiveRequest->receive_request();
        }
        else
        {
            qDebug() << "No receiver to emit request j-j";
        }

        return receiverToReceiveRequest;
    }

    Processor *return_request()
    {
        if (!return_receiver_)
        {
            qDebug() << "Return receiver is not defined!";
            return nullptr;
        }
        return_receiver_->receive_request();
        return return_receiver_;
    }

private:
    Generator generator_;
    std::vector<Processor *> receivers_;
    Processor *return_receiver_;
    int n_generated_requests_;

public:
    double next_event_time;
    std::vector<double> pReturns;
};

class RequestProcessor : public RequestGenerator, public Processor
{
public:
    using Generator = RequestGenerator::Generator;

    RequestProcessor(Generator generator, int max_queue_size = 0, double p_return = 0.0)
    : RequestGenerator(generator)
    , Processor()
    , n_queued_requests_(0)
    , max_queue_size_(max_queue_size)
    , n_processed_requests_(0)
    , n_dropped_requests_(0)
    , n_return_(0)
    , p_return_(p_return)
    {
    }

    ~RequestProcessor() override {}

    int n_queued_requests() const { return n_queued_requests_; }
    int n_processed_requests() const { return n_processed_requests_; }
    int n_dropped_requests() const { return n_dropped_requests_; }

    void process()
    {
        if (n_queued_requests_ > 0)
        {
            ++n_processed_requests_;
            --n_queued_requests_;
            emit_request();

            if (getUniformReal(0, 1) < p_return_)
            {
                ++n_return_;
                return_request();
            }
        }
        next_event_time = n_queued_requests_ ? currentTime + generate_time() : 0.0;
    }

    bool receive_request() override
    {
        const auto cond = max_queue_size_ == 0 || n_queued_requests_ < max_queue_size_;
        if (cond)
        {
            ++n_queued_requests_;
            next_event_time = n_queued_requests_ ? currentTime + generate_time() : 0.0;
        }
        else
        {
            ++n_dropped_requests_;
        }
        return cond;
    }

private:
    int n_queued_requests_;
    int max_queue_size_;
    int n_processed_requests_;
    int n_dropped_requests_;
    int n_return_;
    double p_return_;
};

Results doSimulate(const SimulationParameters &parameters)
{
    RequestGenerator client_generator([=]() {
        return getUniformReal(parameters.client.timeOfCome - parameters.client.timeDelta,
            parameters.client.timeOfCome + parameters.client.timeDelta);
    });

    RequestProcessor terminal(
        [=]() {
            return getUniformReal(
                parameters.terminal.timeOfService - parameters.terminal.timeDelta,
                parameters.terminal.timeOfService + parameters.terminal.timeDelta);
        },
        std::numeric_limits<int>::max());
    std::vector<double> pReturns = {parameters.client.probForSendWindow,
                                    parameters.client.probForGetWindow, parameters.client.probForMoneytalksWindow};
    terminal.pReturns = pReturns;
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

    client_generator.add_receiver(&terminal);
    terminal.add_receiver(&sendWindow);
    terminal.add_receiver(&getWindow);
    terminal.add_receiver(&moneytalksWindow);
    sendWindow.set_return_receiver(&terminal);

    const std::array<RequestGenerator *, 5> devices{
        &client_generator, &terminal, &sendWindow, &getWindow, &moneytalksWindow};

    client_generator.next_event_time = client_generator.generate_time();
    terminal.next_event_time =
        client_generator.next_event_time + terminal.generate_time();
    while (client_generator.n_generated_requests() < parameters.client.amount ||
           terminal.n_queued_requests() > 0 || sendWindow.n_queued_requests() > 0 ||
           getWindow.n_queued_requests() > 0 || moneytalksWindow.n_queued_requests() > 0)
    {
        currentTime = client_generator.next_event_time;
        for (auto &&device : devices)
        {
            if (0.0 < device->next_event_time && device->next_event_time < currentTime)
            {
                currentTime = device->next_event_time;
            }
        }

        for (auto &&device : devices)
        {
            if (currentTime == device->next_event_time)
            {
                auto processor = dynamic_cast<RequestProcessor *>(device);
                if (processor)
                {
                    processor->process();
                }
                else
                {
                    client_generator.emit_request();
                    client_generator.next_event_time =
                        currentTime + client_generator.generate_time();
                }
            }
        }
    }

    const auto res = [](const RequestProcessor &processor) {
        const auto n_dropped_requests = processor.n_dropped_requests();
        const auto n_processed_requests = processor.n_processed_requests();
        const auto p_dropped_requests = static_cast<double>(n_dropped_requests) /
                                        (n_dropped_requests + n_processed_requests);
        return Results::Element{n_dropped_requests, p_dropped_requests};
    };

    return {res(terminal), res(sendWindow), res(getWindow), res(moneytalksWindow)};
}
