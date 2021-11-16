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
int FrequencyTest::findNumberOfSignificantDigits(long number)
{
    int numberOfDigits = std::log10(number) + 1;

    int significantDigits = LONG_SIZE_IN_BITS;
    switch (numberOfDigits)
    {
    case 1:
        significantDigits = 4;
        break;
    case 2:
        significantDigits = 7;
        break;
    case 3:
        significantDigits = 10;
        break;
    }

    return significantDigits;
}

double FrequencyTest::getPValueOfSequence(QVector<long> sequence)
{
    QVector<std::bitset<LONG_SIZE_IN_BITS>> vectorOfLongsBits =
        prepareSequenceBits(sequence);

//    qDebug() << "Sequence in bits:";
//    for (int i = 0; i < vectorOfLongsBits.size(); i++)
//    { qDebug() << vectorOfLongsBits[i].to_string().c_str(); }

    int lengthOfEachBlock = findNumberOfSignificantDigits(sequence[0]);
    qDebug() << "number of sigs: " << lengthOfEachBlock;

    int numberOfAnalyzedBits = lengthOfEachBlock * vectorOfLongsBits.size();
    int numberOfBlocks = numberOfAnalyzedBits / lengthOfEachBlock;

    double sumForStatisic = 0;

    double blockSum, elementOfChiSquaredStat;
    for (int i = 0; i < numberOfBlocks; i++)
    {
        blockSum = 0;
        for (int j = lengthOfEachBlock - 1; j >= 0; j--)
        {
            blockSum += vectorOfLongsBits[i][j];
        }

        elementOfChiSquaredStat = blockSum / lengthOfEachBlock - 0.5;
        sumForStatisic += elementOfChiSquaredStat * elementOfChiSquaredStat;
    }

    double chiSquared = 4 * lengthOfEachBlock * sumForStatisic;

    return incompleteGammaFunction(numberOfBlocks / 2, chiSquared / 2);
}
