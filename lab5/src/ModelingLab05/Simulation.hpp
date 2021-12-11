#pragma once

struct SimulationParameters
{
    struct Client
    {
        int timeOfCome, timeDelta, amountOfProccessedNeeded;
    } client;

    struct Operator
    {
        int timeOfService, timeDelta;
    } operator1, operator2, operator3;

    struct Computer
    {
        int timeOfService;
    } computer1, computer2;
};

struct Results
{
    int numberOfDenials;
    double probabilityOfDenial;
};

Results doSimulate(const SimulationParameters &parameters);
