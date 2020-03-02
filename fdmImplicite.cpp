#include "fdmImplicite.h"
#include "tridiagoLinearSolver.h"
#include <cmath>
#include <fstream>
#include <iostream>

FdmImplicite::FdmImplicite(ReducedPDE *pde, double borneX, int nIntX, double borneT, int nIntT)
{
    pde_ = pde;
    double k = pde_->get_option()->get_k();
    double sigma = pde_->get_option()->get_sigma();
    double T = borneT;

    //pour l'espace
    borneInfX_ = -log(6);
    borneSupX_ = log(borneX / k);
    nIntX_ = nIntX;
    dX_ = (borneSupX_ - borneInfX_) / nIntX_;
    for (int i = 0; i < nIntX_ + 1; i++)
    {
        xVect_.push_back(borneInfX_ + dX_ * i);
    }

    //pour le temps
    borneSupT_ = (T * sigma * sigma) / 2;
    nIntT_ = nIntT;
    dT_ = borneSupT_ / nIntT_;
    for (int i = 0; i < nIntT_ + 1; i++)
    {
        tVect_.push_back(dT_ * i);
    }
    C_ = compute_C();
    set_curInnerSOl();
}

std::vector<double> FdmImplicite::get_xVect() const
{
    return xVect_;
}

std::vector<double> FdmImplicite::get_tVect() const
{
    return tVect_;
}

ReducedPDE* FdmImplicite::get_pde() const {
    return pde_;
}

double FdmImplicite::a_i()
{
    double alf = dT_ / (dX_ * dX_);
    return -alf;
}

double FdmImplicite::b_i()
{
    double alf = dT_ / (dX_ * dX_);
    return 1 + 2 * alf;
}

double FdmImplicite::c_i()
{
    double alf = dT_ / (dX_ * dX_);
    return -alf;
}

std::vector<double> FdmImplicite::get_Correct_xVect() const{
    std::vector<double> data;
    double k = pde_->get_option()->get_k();
    double abscisse;
    for(int i=0; i < nIntX_;i++) {
        abscisse = k * exp(xVect_[i]);
        data.push_back(abscisse);
    }
    return data;
}

TridiagoMatrix FdmImplicite::compute_C()
{
    int size = nIntX_;
    std::vector<double> data;
    data.push_back(b_i());
    data.push_back(c_i());
    for (int i = 2; i < size - 1; i++)
    {
        data.push_back(a_i());
        data.push_back(b_i());
        data.push_back(c_i());
    }
    data.push_back(a_i());
    data.push_back(b_i());
    TridiagoMatrix C(size - 1, size - 1, data);
    return C;
}

void FdmImplicite::set_curInnerSOl()
{
    int size = nIntX_;
    if (i_ == 0)
    {
        std::vector<double> data;
        for (int i = 1; i <= size - 1; i++)
        {
            data.push_back(pde_->initCond(borneInfX_ + i * dX_));
        }
        curInnerSol_ = ColMatrix(size - 1, data);
    }

    else
    {
        double alf = dT_ / (dX_ * dX_);
        std::vector<double> data;
        data.push_back(curInnerSol_[0] + alf * pde_->leftBoundaryCond(i_ * dT_, borneInfX_));
        for (int i = 1; i <= size - 3; i++)
        {
            data.push_back(curInnerSol_[i]);
        }
        data.push_back(curInnerSol_[size - 2] + alf * pde_->rightBoundaryCond(i_ * dT_, borneSupX_));
        ColMatrix Y = ColMatrix(size - 1, data);
        TridiagoLinearSolver syst(&C_, &Y);
        curInnerSol_ = syst.solve();
    }
}

std::vector<double> FdmImplicite::back_to_prices() 
{
    ColMatrix* cM=&curInnerSol_;
    std::vector<double> prices;
    double k = pde_->get_option()->get_k();
    double alpha = pde_->get_alpha();
    double beta = pde_->get_beta();
    double expo = exp(alpha * borneInfX_ + beta * borneSupT_);
    prices.push_back(k * expo * pde_->leftBoundaryCond(borneSupT_, borneInfX_));
    for (int i = 0; i < nIntX_ - 1; i++)
    {
        expo = exp(alpha * xVect_[i + 1] + beta * borneSupT_);
        prices.push_back(k * expo *(*cM)[i]);
    }
    expo = exp(alpha * borneSupX_ + beta * borneSupT_);
    prices.push_back(k * expo * pde_->rightBoundaryCond(borneSupT_, borneSupX_));
    return prices;
}

void FdmImplicite::execute()
{
    if (i_ < nIntT_)
    {
        while (i_ < (nIntT_))
        {
            i_++;
            set_curInnerSOl();
        }
    }
    std::vector<double> prices;
    prices = back_to_prices();
    double abscisse;
    double k = pde_->get_option()->get_k();
    if (pde_->get_option()->get_payoff()->right() == 1)
    {

        std::ofstream fdm_out("fdmCall.csv");
        for (int i = 0; i <= nIntX_; i++)
        {
            abscisse = k * exp(xVect_[i]);
            fdm_out << abscisse << " " << prices[i] << std::endl;
        }
        fdm_out.close();
    }
    else
    {
        std::ofstream fdm_out("fdmPut.csv");
        for (int i = 0; i <= nIntX_; i++)
        {
            abscisse = k * exp(xVect_[i]);
            fdm_out << abscisse << " " << prices[i] << std::endl;
        }
        fdm_out.close();
    }
}
