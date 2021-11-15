#include "tablerandomizer.hpp"

TableRandomizer::TableRandomizer() {}

QVector<long> TableRandomizer::getRandomSequence(
    int numberOfRequiredDigits, int numberOfElements)
{
    if (numberOfRequiredDigits > 5 || numberOfElements < 1)
    {
        return QVector<long>();
    }

    std::fstream fileToRead;
    QVector<long> sequence = QVector<long>();

    long requiredDigitsDivider = pow(10, numberOfRequiredDigits);
    long minAppendValue = requiredDigitsDivider / 10;
    long numberToAppend;
    int addedElements = 0;

    for (fileToRead.open(pathToTable, std::ios_base::in);
         fileToRead >> numberToAppend, addedElements < numberOfElements; addedElements++)
    {
        numberToAppend = numberToAppend % requiredDigitsDivider;
        if (numberToAppend >= minAppendValue)
        {
            sequence.append(numberToAppend);
        }
        else
        {
            addedElements--;
        }
    }

    return sequence;
}
