#include "frequencytest.hpp"
#include "cephes.h"

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

    int n = numberOfSigDigs * vectorOfLongsBits.size();
    int N = n / numberOfSigDigs;

    double sum = 0;

    double blockSum;
    for (int i = 0; i < N; i++)
    {
        blockSum = 0;
        for (int j = numberOfSigDigs - 1; j >= 0; j--)
        {
            blockSum += vectorOfLongsBits[i][j];
        }
        double pi = (double) blockSum / (double) numberOfSigDigs;
        double v = pi - 0.5;
        sum += v * v;
    }

    double chiSquared = 4 * numberOfSigDigs * sum;

    return cephes_igamc(N / 2, chiSquared / 2);
}
