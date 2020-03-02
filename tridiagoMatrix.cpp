#include "tridiagoMatrix.h"
#include <cmath>
#include <iostream>
#include <vector>

TridiagoMatrix::TridiagoMatrix() : BaseMatrix(1, 1), data_()
{
}

TridiagoMatrix::TridiagoMatrix(int nl, int nc, std::vector<double> data) : BaseMatrix(nl, nc), data_(data)
{
    if (nl != nc)
    {
        throw("bad sizes");
    }

    int size = data.size();
    if (size != 3 * nl - 2)
    {
        throw("bad size data");
    }
}

TridiagoMatrix::TridiagoMatrix(TridiagoMatrix const &tDM) : BaseMatrix(tDM.get_nl(), tDM.get_nc()), data_(tDM.get_data()) {}

double TridiagoMatrix::operator()(int i, int j) const
{

    if (i < 0 || i >= nl_ || j < 0 || j >= nc_)
    {
        throw("wrong index");
    }
    if (abs(i - j) >= 2)
    {
        return 0.0;
    }
    if (i == 0)
    {
        if (j == 0 || j == 1)
        {
            return data_[j];
        }
        else
        {
            return 0.0;
        }
    }
    if (i == nl_ - 1)
    {
        if (j == nl_ - 2 || j == nl_ - 1)
        {
            return data_[3 * nl_ - 2 - (nl_ - j)];
        }
        else
        {
            return 0.0;
        }
    }
    else
    {
        return data_[2 + 3 * (i - 1) + j - (i - 1)];
    }
}

std::vector<double> TridiagoMatrix::get_data() const
{
    return data_;
}

double &TridiagoMatrix::operator()(int i, int j)
{

    if (i < 0 || i >= nl_ || j < 0 || j >= nc_)
    {
        throw("wrong index");
    }
    if (abs(i - j) >= 2)
    {
        trash_ = 0;
        return trash_;
    }
    if (i == 0)
    {
        if (j == 0 || j == 1)
        {
            return data_[j];
        }
        else
        {
            trash_ = 0;
            return trash_;
        }
    }
    if (i == nl_ - 1)
    {
        if (j == nl_ - 2 || j == nl_ - 1)
        {
            return data_[3 * nl_ - 2 - (nl_ - j)];
        }
        else
        {
            trash_ = 0;
            return trash_;
        }
    }
    else
    {
        return data_[2 + 3 * (i - 1) + j - (i - 1)];
    }
}

ColMatrix operator*(TridiagoMatrix const &tDM, ColMatrix const &cM)
{
    if (!(tDM.get_nc() == cM.get_nl()))
    {
        throw("sizes not compatible");
    }
    int nl = cM.get_nl();
    ColMatrix M(cM);
    for (int i = 0; i < nl; i++)
    {
        if (i == 0)
        {
            M[i] = tDM(0, 0) * cM[0] + tDM(0, 1) * cM[1];
        }
        else if (i == nl - 1)
        {
            M[i] = tDM(i, nl - 2) * cM[nl - 2] + tDM(i, nl - 1) * cM[nl - 1];
        }
        else
        {
            M[i] = tDM(i, i - 1) * cM[i - 1] + tDM(i, i) * cM[i] + tDM(i, i + 1) * cM[i + 1];
        }
    }
    return M;
}