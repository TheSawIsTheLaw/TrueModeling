#ifndef FREQUENCYTEST_HPP
#define FREQUENCYTEST_HPP

#include <QVector>
#include <cmath>
#include <bitset>

#define LONG_SIZE_IN_BITS sizeof(long) * 8

class FrequencyTest
{
public:
    FrequencyTest();

    double getPValueOfSequence(QVector<long> sequence);

    const double sqrtOfTwo = 1.41421356237309504880;

private:
    int findNumberOfSignificantDigits(QVector<std::bitset<LONG_SIZE_IN_BITS>>);
    QVector<std::bitset<LONG_SIZE_IN_BITS>> prepareSequenceBits(QVector<long> sequence);
};

#endif // FREQUENCYTEST_HPP
