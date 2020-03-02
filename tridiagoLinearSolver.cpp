#include "tridiagoLinearSolver.h"
#include <vector>

TridiagoLinearSolver::TridiagoLinearSolver(TridiagoMatrix *tdM, ColMatrix *cM)
{
    if (tdM->get_nc() != cM->get_nl())
    {
        throw("bad dimension entries");
    }
    tdM_ = tdM;
    cM_ = cM;
}

ColMatrix TridiagoLinearSolver::solve() const
{
    int size = tdM_->get_nl();
    std::vector<double> c_s(size - 1, 0);
    std::vector<double> d_s(size, 0);
    c_s[0] = (tdM_->operator()(0, 1)) / (tdM_->operator()(0, 0));
    d_s[0] = (cM_->operator[](0)) / (tdM_->operator()(0, 0));
    for (int i = 1; i < size; i++)
    {
        if (i < size - 1)
        {
            c_s[i] = (tdM_->operator()(i, i + 1)) / (tdM_->operator()(i, i) - c_s[i - 1] * tdM_->operator()(i, i - 1));
        }
        d_s[i] = (cM_->operator[](i) - d_s[i - 1] * tdM_->operator()(i, i - 1)) / (tdM_->operator()(i, i) - c_s[i - 1] * tdM_->operator()(i, i - 1));
    }

    std::vector<double> d(size, 0);
    d[size - 1] = d_s[size - 1];
    for (int i = size - 2; i >= 0; i--)
    {
        d[i] = d_s[i] - c_s[i] * d[i + 1];
    }
    return ColMatrix(size, d);
}