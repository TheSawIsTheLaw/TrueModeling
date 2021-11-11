#include "gaussMethod.cpp"
#include <QDebug>
#include <QVector>
#include <numeric>

QVector<QVector<double>> buildSystemOfKolmogorovEquations(
    const QVector<QVector<double>> &intensityMatrix)
{
    const auto n = intensityMatrix.size();
    QVector<QVector<double>> result(n, QVector<double>(n + 1));
    for (int state = 0; state < n - 1; state++)
    {
        for (int col = 0; col < n; col++)
        { result[state][state] -= intensityMatrix[state][col]; }
        for (int row = 0; row < n; row++)
        { result[state][row] += intensityMatrix[row][state]; }
    }
    for (int state = 0; state < n; state++) { result[n - 1][state] = 1; }

    result[n - 1][n] = 1;

    return result;
}

QVector<double> probabilityDerivatives(
    const QVector<QVector<double>> &matrix, const QVector<double> &p, double dt)
{
    const auto n = matrix.size();
    QVector<double> dp(n);
    for (int i = 0; i < n; i++)
    {
        double curr = 0;
        for (int j = 0; j < n; j++)
        {
            curr += i != j ? p[j] * matrix[j][i]
                           : p[j] * (matrix[i][i] - std::accumulate(matrix[i].begin(),
                                                        matrix[i].end(), 0.0));
        }
        dp[i] = curr * dt;
    }
    return dp;
}

QVector<double> solve(const QVector<QVector<double>> &intensityMatrix)
{
    QVector<QVector<double>> systemOfKolmogorovEquations =
        buildSystemOfKolmogorovEquations(intensityMatrix);

    return gauss(systemOfKolmogorovEquations);
}

QVector<double> get_system_times(const QVector<QVector<double>> &intensityMatrix,
    const QVector<double> &systemSolvation, const QVector<double> &p0, double dt,
    double eps)
{
    const auto n = intensityMatrix.size();

    QVector<double> time_result(n);
    QVector<double> p = p0;
    bool end = false;
    for (double t = dt; !end && t < 1e3; t += dt)
    {
        end = true;
        QVector<double> dp = probabilityDerivatives(intensityMatrix, p, dt);
        for (int i = 0; i < n; i++)
        {
            end = (std::abs(systemSolvation[i] - p[i]) <= eps) && (dp[i] <= eps);
            !end ?: time_result[i] != 0.0 ?: time_result[i] = t;
            p[i] += dp[i];
        }
    }

    return time_result;
}
