#include "linearcongruentrandomizer.hpp"

LinearCongruentRandomizer::LinearCongruentRandomizer() {}

#include <QDebug>
QVector<long> LinearCongruentRandomizer::createRandomSequence(
    int numberOfRequiredDigits, int numberOfElements)
{
    if (numberOfElements < 1 || numberOfRequiredDigits < 1)
    {
        return QVector<long>();
    }

    QVector<long> sequence = QVector<long>();

    long requiredDigitsDivider = pow(10, numberOfRequiredDigits);
    long minAppendValue = requiredDigitsDivider / 10 - 1;
    long numberToAppend;
    for (int i = 0; i < numberOfElements; i++)
    {
        curElement = curElement * 1103515245 + 12345;
        numberToAppend = ((unsigned int)(curElement / 65536) % (RAND_MAX + 1)) % requiredDigitsDivider;

        if (numberToAppend >= minAppendValue)
        {
            sequence.append(numberToAppend);
        }
        else
        {
            i--;
        }
    }

//    qDebug() << "Generated seq: " << sequence;
    return sequence;
}

void LinearCongruentRandomizer::setSeed(long seed)
{
    curElement = seed;
}
