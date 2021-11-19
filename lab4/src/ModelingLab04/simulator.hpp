#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "processor.hpp"
#include "requestsgenerator.hpp"

#include <QPair>

class Simulator
{
public:
    Simulator(Processor processor_, RequestsGenerator requestGenerator_);

    QPair<double, double> simulateUsingDeltaTMethod(double aParameter, double bParameter,
        double muParameter, double sigmaParameter, double probabilityOfReturn);

    QPair<double, double> simulateUsingEventMethod(double aParameter, double bParameter,
        double muParameter, double sigmaParameter, double probabilityOfReturn);

private:
    Processor processor;
    RequestsGenerator requestGenerator;
};

#endif // SIMULATOR_HPP
