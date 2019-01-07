//
// Created by Michael on 12/27/17.
//

#include <cmath>
#include <iostream>
#include <iomanip>
#include "mingw.thread.h"
#include "GaussJordanElimination.hpp"

GaussJordanElimination::Vect
GaussJordanElimination::solve(const GaussJordanElimination::Matrix& A, const GaussJordanElimination::Vect& B)
{
    int n = A.size();
    if (A[0].size() != n || B.size() != n)
        return Vect();

    Matrix Aug = buildAugmentedMatrix(A, B);
    reduce(Aug);
    return extractSolution(Aug);
}

GaussJordanElimination::Matrix GaussJordanElimination::buildAugmentedMatrix(const GaussJordanElimination::Matrix& A,
                                                                            const GaussJordanElimination::Vect& B)
{
    Matrix Aug(A);
    for (int i = 0; i < Aug.size(); ++i)
        Aug[i].push_back(B[i]);
    return Aug;
}

void GaussJordanElimination::reduce(GaussJordanElimination::Matrix& Aug)
{
    int n = Aug.size();
    for (int p = 0; p < n; ++p) {

        int max = p;
        for (int i = p + 1; i < n; ++i)
        {
            if (std::abs(Aug[i][p]) > std::abs(Aug[max][p]))
                max = i;
        }

        swapRowsByIndices(Aug, p, max);

        if (std::abs(Aug[p][p]) <= EPS)
            continue;

        pivot(Aug, p, p);
    }
}

GaussJordanElimination::Vect GaussJordanElimination::extractSolution(GaussJordanElimination::Matrix& Aug)
{
    int n = Aug.size();
    Vect solution = Vect(n);
    for (int i = 0; i < n; i++)
    {
        if (std::abs(Aug[i][i]) > EPS)
            solution[i] = Aug[i][n] / Aug[i][i];
        else if (std::abs(Aug[i][n]) > EPS)
            return Vect();
    }
    return solution;
}

void GaussJordanElimination::swapRowsByIndices(GaussJordanElimination::Matrix& matrix, int i, int j)
{
    //std::swap(matrix[i], matrix[j]);
    auto temp = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = temp;
}

void GaussJordanElimination::pivot(GaussJordanElimination::Matrix& matrix, int p, int q)
{
    int n = matrix.size();

    std::vector<std::thread> pool;
    for (int i = 0; i < n; i++)
    {
        if (i != p)
            pool.push_back(std::thread(&GaussJordanElimination::processPivotLine, this, std::ref(matrix[i]), matrix[p], q));
    }
    for (auto& x: pool) x.join();

    for (int i = 0; i < n; i++)
    {
        if (i != p)
            matrix[i][q] = 0;
    }

    for (int j = 0; j <= n; j++)
    {
        if (j != q)
            matrix[p][j] /= matrix[p][q];
    }

    matrix[p][q] = 1.0;
}

void GaussJordanElimination::processPivotLine(GaussJordanElimination::Vect& matrixi,
                                              const GaussJordanElimination::Vect& matrixp,
                                              int q)
{
    double alpha = matrixi[q] / matrixp[q];
    for (int j = 0; j < matrixi.size(); j++)
    {
        if (j != q)
            matrixi[j] -= alpha * matrixp[j];
    }
}
