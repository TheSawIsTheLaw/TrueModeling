#include "gaussMethod.cpp"
#include <QDebug>
#include <QVector>
#include <numeric>

QVector<QVector<double>> buildSystemOfKolmogorovEquations(
    const QVector<QVector<double>> &intensityMatrix)
{
    int numberOfStates = intensityMatrix.size();

    QVector<QVector<double>> result(numberOfStates, QVector<double>(numberOfStates + 1));
    for (int curState = 0; curState < numberOfStates - 1; curState++)
    {
        for (int col = 0; col < numberOfStates; col++)
        { result[curState][curState] -= intensityMatrix[curState][col]; }

        for (int row = 0; row < numberOfStates; row++)
        { result[curState][row] += intensityMatrix[row][curState]; }
    }

    for (int state = 0; state < numberOfStates; state++)
    { result[numberOfStates - 1][state] = 1; }

    result[numberOfStates - 1][numberOfStates] = 1;

    return result;
}

QVector<double> probabilityDerivatives(const QVector<QVector<double>> &intensityMetrix,
    const QVector<double> &probabilities, double timeDelta)
{
    int numberOfStates = intensityMetrix.size();

    QVector<double> probabilityDerivatives(numberOfStates);
    for (int i = 0; i < numberOfStates; i++)
    {
        double sumForProbability = 0;
        for (int j = 0; j < numberOfStates; j++)
        {
            sumForProbability +=
                i != j
                    ? probabilities[j] * intensityMetrix[j][i]
                    : probabilities[j] * (intensityMetrix[i][i] -
                                             std::accumulate(intensityMetrix[i].begin(),
                                                 intensityMetrix[i].end(), 0.0));
        }

        probabilityDerivatives[i] = sumForProbability * timeDelta;
    }

    return probabilityDerivatives;
}

QVector<double> solve(const QVector<QVector<double>> &intensityMatrix)
{
    QVector<QVector<double>> systemOfKolmogorovEquations =
        buildSystemOfKolmogorovEquations(intensityMatrix);

    return gauss(systemOfKolmogorovEquations);
}

QVector<double> determineTime(const QVector<QVector<double>> &intensityMatrix,
    const QVector<double> &systemSolvation, const QVector<double> &probabilityList,
    double timeDelta, double eps)
{
    int numberOfStates = intensityMatrix.size();

    QVector<double> listOfTimes(numberOfStates);
    QVector<double> probabilities = probabilityList;

    bool endOfSearchCondition = false;
    for (double curTime = timeDelta; !endOfSearchCondition && curTime < 1e3;
         curTime += timeDelta)
    {
        endOfSearchCondition = true;
        QVector<double> probabilityDerivative =
            probabilityDerivatives(intensityMatrix, probabilities, timeDelta);
        for (int i = 0; i < numberOfStates; i++)
        {
            endOfSearchCondition =
                (std::abs(systemSolvation[i] - probabilities[i]) <= eps) &&
                (probabilityDerivative[i] <= eps);

            !endOfSearchCondition ?: listOfTimes[i] != 0.0 ?: listOfTimes[i] = curTime;

            probabilities[i] += probabilityDerivative[i];
        }
    }

    return listOfTimes;
}
