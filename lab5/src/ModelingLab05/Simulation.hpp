#pragma once

struct SimulationParameters
{
    int time, timeDelta;
    int numberOfRequests;

    struct Operator
    {
        int serviceTime, timeDelta;
    } operator1, operator2, operator3;

    struct Computer
    {
        int serviceTime;
    } computer1, computer2;
};

struct Results
{
    int numberOfDenials;
    double probabilityOfDenial;
};

Results doSimulate(const SimulationParameters &parameters);
