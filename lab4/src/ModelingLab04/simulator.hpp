#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "modelingElements.hpp"

#include <QPair>

class Simulator
{
public:
    Simulator();
    Simulator(Processor processor_, RequestsGenerator requestGenerator_);

    QPair<double, double> simulateUsingDeltaTMethod(size_t numberOfRequests);

    QPair<double, double> simulateUsingEventMethod(size_t numberOfRequests);

private:
    Processor processor;
    RequestsGenerator requestGenerator;
};

#endif // SIMULATOR_HPP
