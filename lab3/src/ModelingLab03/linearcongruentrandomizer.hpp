#ifndef LINEARCONGRUENTRANDOMIZER_HPP
#define LINEARCONGRUENTRANDOMIZER_HPP

#include <QVector>
#include <cmath>

class LinearCongruentRandomizer
{
public:
    LinearCongruentRandomizer();

    QVector<long int> createRandomSubsequence(int numberOfRequiredDigits, int numberOfElements);
    void setSeed(long seed);

private:
    long int curElement = 1;
};

#endif // LINEARCONGRUENTRANDOMIZER_HPP
