#include <QVector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

bool is_square_matrix(const QVector<QVector<double>> &matrix)
{
    for (const auto &row : matrix)
    {
        if (!(row.size() == matrix.size() + 1))
        {
            return false;
        }
    }
    return true;
}

decltype(auto) max_abs_element_in_column(
    QVector<QVector<double>> &matrix, typename QVector<double>::size_type col)
{
    return std::max_element(matrix.begin() + col, matrix.end(),
        [col](const QVector<double> &lhs, const QVector<double> &rhs) {
            return fabs(lhs[col]) < fabs(rhs[col]);
        });
}

void make_zeros(
    QVector<QVector<double>> &matrix, typename QVector<double>::size_type col)
{
    using size_type = typename QVector<double>::size_type;

    for (size_type i = col + 1; i < matrix.size(); ++i)
    {
        const auto d = -matrix[i][col] / matrix[col][col];
        matrix[i][col] = 0;
        for (size_type j = col + 1; j < matrix[0].size(); ++j)
        { matrix[i][j] += d * matrix[col][j]; }
    }
}

QVector<double> gauss(const QVector<QVector<double>> &A)
{
    const auto n = A.size();

    if (!n || !is_square_matrix(A))
    {
        throw std::invalid_argument("Inappropriate dimensions");
    }

    auto G = A;
    for (int k = 0; k < n; ++k)
    {
        auto max_abs_row = max_abs_element_in_column(G, k);
        std::swap(*max_abs_row, G[k]);
        make_zeros(G, k);

        if (fabs(G[k][k]) < std::numeric_limits<double>::epsilon())
        {
            throw std::invalid_argument("hmm");
        }
    }

    QVector<double> X(n);
    for (int i = static_cast<int>(n) - 1; i >= 0; --i)
    {
        const auto j = static_cast<int>(i);
        X[j] = G[j][n] / G[j][j];
        for (int k = i - 1; k >= 0; --k)
        {
            const auto q = static_cast<int>(k);
            G[q][n] -= G[q][j] * X[j];
        }
    }

    return X;
}
