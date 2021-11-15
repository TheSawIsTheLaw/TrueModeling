#ifndef TABLERANDOMIZER_HPP
#define TABLERANDOMIZER_HPP

#include <QVector>
#include <string>
#include <fstream>
#include <cmath>

class TableRandomizer
{
public:

    TableRandomizer();
    ~TableRandomizer();

    QVector<long> getRandomSequence(int numberOfRequiredDigits, int numberOfElements);

private:
    std::string pathToTable = "numbersFromAMRDWND.txt";
    size_t curElementIndex = 0;
    std::fstream fileToRead;
};

#endif // TABLERANDOMIZER_HPP
