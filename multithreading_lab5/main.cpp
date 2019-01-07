#include <iostream>
#include <vector>
#include <cmath>
#include "GaussJordanElimination.hpp"

typedef std::vector<double> Vect;
typedef std::vector<std::vector<double>> Matrix;
bool validate(const Matrix& A, const Vect& B, const Vect& X);

int main()
{
    const Matrix A =
            {
                    {1, 2, 1},
                    {4, 1, 3},
                    {3, 7, 5}
            };
    const Vect B = {8, 15, 32};
    Vect X = GaussJordanElimination().solve(A, B);

    for (int i = 0; i < X.size(); ++i) std::cout<<X[i]<<" ";
    std::cout<<(validate(A, B, X) ? "Correct" : "Error");
}

bool validate(const Matrix& A, const Vect& B, const Vect& X)
{
    int n = A.size();
    if (A[0].size() != n || B.size() != n || X.size() != n)
        return false;

    for (int i = 0; i < n; ++i)
    {
        double sum = 0;

        for (int j = 0; j < n; ++j)
            sum += A[i][j] * X[j];

        if (std::abs(sum - B[i]) > 1e-8)
            return false;
    }

    return true;
}