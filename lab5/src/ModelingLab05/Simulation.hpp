#pragma once

struct SimulationParameters
{
    struct Client
    {
        double timeOfCome, timeDelta;
        int amount;
        double probForSendWindow, probForGetWindow, probForMoneytalksWindow, probabilityOfReturnToMainQueue;
    } client;

    struct Terminal
    {
        double timeOfService, timeDelta;
    } terminal;

    struct Window
    {
        double timeOfService, timeDelta;
        int maxQueueSize;
    } sendWindow, getWindow, moneytalksWindow;
};

struct Results
{
    struct Element
    {
        int numberOfDenials;
        double probabilityOfDenial;
    } terminal, sendWindow, getWindow, moneytalksWindow;
};

Results doSimulate(SimulationParameters &parameters);
