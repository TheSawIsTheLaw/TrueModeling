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

int FrequencyTest::findNumberOfSignificantDigits(QVector<std::bitset<LONG_SIZE_IN_BITS>> vectorOfLongsBits)
{
    int currentMaxOfSigDigs = 0;
    for (size_t i = 0; i < vectorOfLongsBits.size(); i++)
    {
        size_t j = LONG_SIZE_IN_BITS - 1;
        for (; vectorOfLongsBits[i][j] == 0 && j > 0; j--) {}
        if (j > currentMaxOfSigDigs) currentMaxOfSigDigs = j + 1;
    }

    return currentMaxOfSigDigs;
}

#include <QDebug>
double FrequencyTest::getPValueOfSequence(QVector<long> sequence)
{
    QVector<std::bitset<LONG_SIZE_IN_BITS>> vectorOfLongsBits =
        prepareSequenceBits(sequence);

    qDebug() << "Sequence in bits:";
    for (int i = 0; i < vectorOfLongsBits.size(); i++)
    { qDebug() << vectorOfLongsBits[i].to_string().c_str(); }

    int numberOfSigDigs = findNumberOfSignificantDigits(vectorOfLongsBits);
    qDebug() << "number of sigs: " << numberOfSigDigs;
    long long sum = 0;
    for (int i = 0; i < vectorOfLongsBits.size(); i++)
    {
        size_t j = numberOfSigDigs - 1;

        for (; j > 0; j--)
        {
            sum += 2 * vectorOfLongsBits[i][j] - 1;
        }
    }
    qDebug() << "sum" << sum;
    qDebug() << "sequence of" << sequence[0];

    size_t numberOfUsedBits = vectorOfLongsBits.size() * numberOfSigDigs;
    double sObs = abs(sum) / sqrt(numberOfUsedBits);

    qDebug() << "sObs" << sObs;

    // If the computed P-value is < 0.01, then conclude that the sequence is non-random
    return erfc(sObs / sqrtOfTwo);
}
