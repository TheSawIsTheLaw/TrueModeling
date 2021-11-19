#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "processor.hpp"
#include "requestsgenerator.hpp"

class Simulator
{
public:
    Simulator(Processor processor_, RequestsGenerator);

private:
    Processor processor;
    RequestsGenerator requestGenerator;
};

#endif // SIMULATOR_HPP
