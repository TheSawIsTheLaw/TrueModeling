#include "frequencytest.hpp"

FrequencyTest::FrequencyTest() {}

QVector<std::bitset<LONG_SIZE_IN_BITS>> FrequencyTest::prepareSequenceBits(
    QVector<long> sequence)
{
    QVector<std::bitset<LONG_SIZE_IN_BITS>> outSeq;

    for (int i = 0; i < sequence.size(); i++)
    { outSeq.append(std::bitset<LONG_SIZE_IN_BITS>(sequence[i])); }

    return outSeq;
}

#include <QDebug>
int FrequencyTest::findNumberOfSignificantDigits(QVector<std::bitset<LONG_SIZE_IN_BITS>> vectorOfLongsBits)
{
    int currentMaxOfSigDigs = 0;
    for (int i = 0; i < vectorOfLongsBits.size(); i++)
    {
        int j = LONG_SIZE_IN_BITS - 1;
        for (; vectorOfLongsBits[i][j] == 0 && j >= 0; j--) {}
        if (j > currentMaxOfSigDigs) currentMaxOfSigDigs = j;
    }

    return currentMaxOfSigDigs + 1;
}

double FrequencyTest::getPValueOfSequence(QVector<long> sequence)
{
    QVector<std::bitset<LONG_SIZE_IN_BITS>> vectorOfLongsBits =
        prepareSequenceBits(sequence);

//    qDebug() << "Sequence in bits:";
//    for (int i = 0; i < vectorOfLongsBits.size(); i++)
//    { qDebug() << vectorOfLongsBits[i].to_string().c_str(); }

    int numberOfSigDigs = findNumberOfSignificantDigits(vectorOfLongsBits);
    qDebug() << "number of sigs: " << numberOfSigDigs;
    int numberOfUsedBits = 0;
    long long sum = 0;
    for (int i = 0; i < vectorOfLongsBits.size(); i++)
    {
        for (int j = numberOfSigDigs - 1; j >= 0; numberOfUsedBits++, j--)
        {
            sum += 2 * vectorOfLongsBits[i][j] - 1;
        }
    }
    qDebug() << "sum" << sum;
    qDebug() << "number of used bits" << numberOfUsedBits;
    qDebug() << "sequence of" << sequence[0];

//    size_t numberOfUsedBits = vectorOfLongsBits.size() * numberOfSigDigs;
    double sObs = abs(sum) / sqrt(numberOfUsedBits);

    qDebug() << "sObs" << sObs;

    // If the computed P-value is < 0.01, then conclude that the sequence is non-random
    return erfc(sObs / sqrtOfTwo);
}
