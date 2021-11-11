#include "gaussMethod.cpp"
#include <QVector>
#include <numeric>

QVector<QVector<double>> build_coeff_matrix(const QVector<QVector<double>> &matrix)
{
    const auto n = matrix.size();
    QVector<QVector<double>> result(n, QVector<double>(n + 1));
    for (int state = 0; state < n - 1; ++state)
    {
        for (int col = 0; col < n; ++col) { result[state][state] -= matrix[state][col]; }
        for (int row = 0; row < n; ++row) { result[state][row] += matrix[row][state]; }
    }
    for (int state = 0; state < n; ++state) { result[n - 1][state] = 1; }

    result[n - 1][n] = 1;

    return result;
}

QVector<double> delta_p(
    const QVector<QVector<double>> &matrix, const QVector<double> &p, double dt)
{
    const auto n = matrix.size();
    QVector<double> dp(n);
    for (int i = 0; i < n; ++i)
    {
        double curr = 0;
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                curr += p[j] * (matrix[i][i] - std::accumulate(matrix[i].begin(),
                                                   matrix[i].end(), 0.0));
            }
            else
            {
                curr += p[j] * matrix[j][i];
            }
        }
        dp[i] = curr * dt;
    }
    return dp;
}

QVector<double> solve(const QVector<QVector<double>> &matrix)
{
    return gauss(build_coeff_matrix(matrix));
}

QVector<double> get_system_times(const QVector<QVector<double>> &matrix,
    const QVector<double> &result, const QVector<double> &p0, double dt, double eps)
{
    using size_type = typename QVector<double>::size_type;

    const auto n = matrix.size();

    QVector<double> time_result(n);
    QVector<double> p = p0;
    for (auto [t, end] = std::tuple{dt, false}; !end && t < 1000; t += dt)
    {
        end = true;
        auto dp = delta_p(matrix, p, dt);
        for (size_type i = 0; i < n; ++i)
        {
            if (std::abs(result[i] - p[i]) <= eps && dp[i] <= eps)
            {
                if (time_result[i] == 0.0)
                {
                    time_result[i] = t;
                }
            }
            else
            {
                end = false;
            }
            p[i] += dp[i];
        }
    }

    return time_result;
}
