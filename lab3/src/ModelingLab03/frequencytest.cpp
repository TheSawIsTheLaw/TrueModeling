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
double FrequencyTest::getPValueOfSequence(QVector<long> sequence)
{
    QVector<std::bitset<LONG_SIZE_IN_BITS>> vectorOfLongsBits =
        prepareSequenceBits(sequence);

    qDebug() << "Sequence in bits:";
    for (int i = 0; i < vectorOfLongsBits.size(); i++)
    { qDebug() << vectorOfLongsBits[i].to_string().c_str(); }

    double sum = 0.0;
    size_t numberOfUsedBits = 0;
    for (int i = 0; i < vectorOfLongsBits.size(); i++)
    {
        size_t j = LONG_SIZE_IN_BITS - 1;
        for (; vectorOfLongsBits[i][j] == 0 && j > 0; j--) {}

        numberOfUsedBits = j + 1;
        for (; j > 0; j--)
        {
            sum += 2 * vectorOfLongsBits[i][j] - 1;
        }
    }
    qDebug() << "sum" << sum;

    double sObs = fabs(sum) / sqrt(numberOfUsedBits);

    // If the computed P-value is < 0.01, then conclude that the sequence is non-random
    return erfc(sObs / sqrtOfTwo);
}
