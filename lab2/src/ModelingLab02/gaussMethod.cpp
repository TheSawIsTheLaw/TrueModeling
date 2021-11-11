#include <QVector>
#include <algorithm>
#include <cmath>

QVector<double> *getRowWithMaxAbsInColumn(QVector<QVector<double>> &system, int col)
{
    return std::max_element(system.begin() + col, system.end(),
        [col](const QVector<double> &lhs, const QVector<double> &rhs) {
            return fabs(lhs[col]) < fabs(rhs[col]);
        });
}

void columnZeroing(QVector<QVector<double>> &matrix, int col)
{
    for (int i = col + 1; i < matrix.size(); i++)
    {
        double d = -matrix[i][col] / matrix[col][col];
        matrix[i][col] = 0;
        for (int j = col + 1; j < matrix[0].size(); j++)
        { matrix[i][j] += d * matrix[col][j]; }
    }
}

QVector<double> gauss(const QVector<QVector<double>> &systemToSolve)
{
    int n = systemToSolve.size();

    QVector<QVector<double>> triangleSystem = systemToSolve;
    for (int k = 0; k < n; k++)
    {
        QVector<double> *changedRowToLift = getRowWithMaxAbsInColumn(triangleSystem, k);
        std::swap(*changedRowToLift, triangleSystem[k]);
        columnZeroing(triangleSystem, k);
    }

    QVector<double> fundamentalDecisionSystem(n);
    for (int i = n - 1; i >= 0; i--)
    {
        fundamentalDecisionSystem[i] = triangleSystem[i][n] / triangleSystem[i][i];
        for (int k = i - 1; k >= 0; k--)
        { triangleSystem[k][n] -= triangleSystem[k][i] * fundamentalDecisionSystem[i]; }
    }

    return fundamentalDecisionSystem;
}
