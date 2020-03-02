
#include "crankNicholson.h"
#include "tridiagoLinearSolver.h"
#include <fstream>
#include <iostream>

CrankNicholson::CrankNicholson(BlackScholesPDE *pde, double borneX, int nIntX, double borneT, int nIntT)
{
    pde_ = pde;

    //sur l'espace
    borneX_ = borneX;
    nIntX_ = nIntX;
    dX_ = borneX_ / nIntX_;
    for (int i = 0; i < nIntX + 1; i++)
    {
        xVect_.push_back(dX_ * i);
    }

    //sur le temps
    borneT_ = borneT;
    nIntT_ = nIntT;
    dT_ = borneT_ / nIntT_;
    for (int i = 0; i < nIntT_ + 1; i++)
    {
        tVect_.push_back(dT_ * i);
    }

    C_ = compute_C();
    D_ = compute_D();
    set_prevAndCurInnerSOl();
    set_prevAndCurBoundaries();
}

TridiagoMatrix CrankNicholson::compute_C()
{
    int size = nIntX_;
    std::vector<double> data;
    data.push_back(1 - b_i(1));
    data.push_back(-c_i(1));
    for (int i = 2; i <= size - 2; i++)
    {
        data.push_back(-a_i(i));
        data.push_back(1 - b_i(i));
        data.push_back(-c_i(i));
    }
    data.push_back(-a_i(size - 1));
    data.push_back(1 - b_i(size - 1));
    TridiagoMatrix C(size - 1, size - 1, data);
    return C;
}

TridiagoMatrix CrankNicholson::compute_D()
{
    int size = nIntX_;
    std::vector<double> data;
    data.push_back(1 + b_i(1));
    data.push_back(c_i(1));
    for (int i = 2; i <= size - 2; i++)
    {
        data.push_back(a_i(i));
        data.push_back(1 + b_i(i));
        data.push_back(c_i(i));
    }
    data.push_back(a_i(size - 1));
    data.push_back(1 + b_i(size - 1));
    TridiagoMatrix D(size - 1, size - 1, data);
    return D;
}

void CrankNicholson::set_prevAndCurInnerSOl()
{
    if (i_ == 0)
    {
        std::vector<double> data;
        for (int i = 0; i < nIntX_ - 1; i++)
        {
            data.push_back(pde_->initCond(xVect_[i + 1]));
        }
        curInnerSol_ = ColMatrix(nIntX_ - 1, data);
    }

    else
    {
        prevInnerSol_ = curInnerSol_;
        ColMatrix Y = D_ * prevInnerSol_ + prevBoundaries_ + curBoundaries_;
        TridiagoLinearSolver syst(&C_, &Y);
        curInnerSol_ = syst.solve();
        ColMatrix check = C_ * curInnerSol_;
    }
}

void CrankNicholson::set_prevAndCurBoundaries()
{
    if (i_ == 0)
    {
        std::vector<double> data;
        data.push_back(a_i(1) * pde_->leftBoundaryCond(borneT_));
        for (int i = 1; i < nIntX_ - 2; i++)
        {
            data.push_back(0);
        }
        data.push_back(c_i(nIntX_ - 1) * pde_->rightBoundaryCond(borneT_, borneX_));
        curBoundaries_ = ColMatrix(nIntX_ - 1, data);
    }
    else
    {
        prevBoundaries_ = curBoundaries_;
        std::vector<double> data;
        data.push_back(a_i(1) * pde_->leftBoundaryCond(borneT_ - i_ * dT_));
        for (int i = 1; i < nIntX_ - 2; i++)
        {
            data.push_back(0);
        }
        data.push_back(c_i(nIntX_ - 1) * pde_->rightBoundaryCond(borneT_ - i_ * dT_, borneX_));
        curBoundaries_ = ColMatrix(nIntX_ - 1, data);
    }
}

double CrankNicholson::a_i(int i)
{
    double sigma = pde_->get_option()->get_sigma();
    double r = pde_->get_option()->get_r();
    return (dT_ / 4) * (sigma * sigma * i * i - r * i);
}

double CrankNicholson::b_i(int i)
{
    double sigma = pde_->get_option()->get_sigma();
    double r = pde_->get_option()->get_r();
    return (-dT_ / 2) * (sigma * sigma * i * i + r);
}

double CrankNicholson::c_i(int i)
{
    double sigma = pde_->get_option()->get_sigma();
    double r = pde_->get_option()->get_r();
    return (dT_ / 4) * (sigma * sigma * i * i + r * i);
}

std::vector<double> CrankNicholson::get_xVect() const
{
    return xVect_;
}
std::vector<double> CrankNicholson::get_tVect() const
{
    return tVect_;
}

BlackScholesPDE *CrankNicholson::get_pde() const
{
    return pde_;
}

ColMatrix CrankNicholson::get_curSol() const
{
    return curInnerSol_;
}
void CrankNicholson::execute()
{
    if (i_ < nIntT_)
    {
        while (i_ < (nIntT_))
        {
            i_++;
            set_prevAndCurBoundaries();
            set_prevAndCurInnerSOl();
        }
    }
    if (pde_->get_option()->get_payoff()->right() == 1)
    {

        std::ofstream fdm_out("crankCall.csv");
        fdm_out << 0 << " " << curBoundaries_[0] / a_i(1) << std::endl;
        for (int i = 1; i < nIntX_; i++)
        {
            fdm_out << xVect_[i] << " " << curInnerSol_[i - 1] << std::endl;
        }
        fdm_out << borneX_ << " " << curBoundaries_[nIntX_ - 2] / c_i(nIntX_ - 1) << std::endl;
        fdm_out.close();
    }

    else
    {
        std::ofstream fdm_out("crankPut.csv");
        fdm_out << 0 << " " << curBoundaries_[0] / a_i(1) << std::endl;
        for (int i = 1; i < nIntX_; i++)
        {
            fdm_out << xVect_[i] << " " << curInnerSol_[i - 1] << std::endl;
        }
        fdm_out << borneX_ << " " << curBoundaries_[nIntX_ - 2] / c_i(nIntX_ - 1) << std::endl;
        fdm_out.close();
    }
}