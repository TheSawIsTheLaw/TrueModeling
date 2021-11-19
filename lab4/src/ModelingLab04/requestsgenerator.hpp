#ifndef REQUESTSGENERATOR_HPP
#define REQUESTSGENERATOR_HPP

#include "distributions.cpp"

class RequestsGenerator
{
public:
    RequestsGenerator();
    RequestsGenerator(double muParameter_, double sigmaParameter_);

    double getNextTimeOfRequestGenerated();

private:
    double muParameter = 0;
    double sigmaParameter = 1;
};

#endif // REQUESTSGENERATOR_HPP
