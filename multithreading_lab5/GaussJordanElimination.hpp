//
// Created by Michael on 12/27/17.
//

#ifndef MULTITHREADING_LAB5_GAUSSJORDANELIMINATION_HPP
#define MULTITHREADING_LAB5_GAUSSJORDANELIMINATION_HPP

#include <vector>
#include "mingw.mutex.h"

class GaussJordanElimination
{
    typedef std::vector<double> Vect;
    typedef std::vector<std::vector<double>> Matrix;
    const double EPS = 1E-8;
    std::mutex mtx;

    Matrix buildAugmentedMatrix(const Matrix& A, const Vect& B);
    void reduce(Matrix& Aug);
    Vect extractSolution(Matrix& Aug);
    void swapRowsByIndices(Matrix& matrix, int i, int j);
    void pivot(Matrix& matrix, int p, int q);
    void processPivotLine(Vect& matrixi, const Vect& matrixp, int q);
public:
    Vect solve(const Matrix& A, const Vect& B);
};


#endif //MULTITHREADING_LAB5_GAUSSJORDANELIMINATION_HPP
