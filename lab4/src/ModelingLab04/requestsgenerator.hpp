#ifndef REQUESTSGENERATOR_HPP
#define REQUESTSGENERATOR_HPP

#include "distributions.cpp"

class RequestsGenerator
{
public:
    RequestsGenerator(double muParameter_, double sigmaParameter_);

    double getNextTimeOfRequestGenerated();

private:
    double muParameter;
    double sigmaParameter;
};

#endif // REQUESTSGENERATOR_HPP
