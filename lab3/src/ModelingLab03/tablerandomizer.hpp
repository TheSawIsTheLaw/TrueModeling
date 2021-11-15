#ifndef TABLERANDOMIZER_HPP
#define TABLERANDOMIZER_HPP

#include <QVector>
#include <string>
#include <fstream>
#include <cmath>

class TableRandomizer
{
public:
    std::string pathToTable = "numbersFromAMRDWND.txt";

    TableRandomizer();

    QVector<long> getRandomSequence(int numberOfRequiredDigits, int numberOfElements);

private:
    size_t curElementIndex = 0;
};

#endif // TABLERANDOMIZER_HPP
