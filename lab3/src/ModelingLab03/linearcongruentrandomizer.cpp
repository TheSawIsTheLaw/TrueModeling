#include "linearcongruentrandomizer.hpp"

LinearCongruentRandomizer::LinearCongruentRandomizer() {}

QVector<long> LinearCongruentRandomizer::createRandomSubsequence(
    int numberOfRequiredDigits, int numberOfElements)
{
    if (numberOfElements < 1 || numberOfRequiredDigits < 1)
    {
        return QVector<long>();
    }

    QVector<long> subsequence = QVector<long>();

    long requiredDigitsDivider = pow(10, numberOfRequiredDigits);
    long minAppendValue = requiredDigitsDivider / 10;
    long numberToAppend;
    for (int i = 0; i < numberOfElements; i++)
    {
        curElement = curElement * 1103515245 + 12345;
        numberToAppend = ((unsigned int)(curElement / 65536) % (RAND_MAX + 1)) % requiredDigitsDivider;

        if (numberToAppend < minAppendValue)
        {
            i--;
        }
        else
        {
            subsequence.append(numberToAppend);
        }
    }

    return subsequence;
}

void LinearCongruentRandomizer::setSeed(long seed)
{
    curElement = seed;
}
