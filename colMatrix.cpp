#include "colMatrix.h"

ColMatrix::ColMatrix(): BaseMatrix(1,1),data_(){}

ColMatrix::ColMatrix(int nl, std::vector<double> data) : BaseMatrix(nl, 1), data_(data)
{
    if (nl <= 0)
    {
        throw("bad size");
    }

    int size = data.size();
    if (nl != size )
    {
        throw("bad size data");
    }
}

ColMatrix::ColMatrix(BaseMatrix const &bM, std::vector<double> data) : BaseMatrix(bM), data_(data) {}

ColMatrix::ColMatrix(ColMatrix const &cM) : BaseMatrix(cM.get_nl(), 1), data_(cM.get_data()) {}

double ColMatrix::operator[](int i) const
{
    if (i < 0 || i >= nl_)
    {
        throw("bad index");
    }
    else
    {
        return data_[i];
    }
}

double &ColMatrix::operator[](int i)
{
    if (i < 0 || i >= nl_)
    {
        throw("bad index");
    }
    else
    {
        return data_[i];
    }
}
std::vector<double> ColMatrix::get_data() const
{
    return data_;
}

ColMatrix operator*(double d, ColMatrix const &cM)
{
    ColMatrix newcM(cM);
    for (int i = 0; i < cM.get_nl(); i++)
    {
        double tmp = newcM[i];
        newcM[i] = d * tmp;
    }
    return newcM;
}

ColMatrix operator+(ColMatrix const &cM1, ColMatrix const &cM2)
{
    if (cM1.get_nl() != cM2.get_nl())
    {
        throw("bad sizes");
    }
    ColMatrix newcM(cM1);
    for (int i = 0; i < newcM.get_nl(); i++)
    {
        double tmp = newcM[i] + cM2[i];
        newcM[i] = tmp;
    }
    return newcM;
}
