#include "blackScholesPDE.h"
#include <math.h>

BlackScholesPDE::BlackScholesPDE(EurOption *option) : option_(option) {}

double BlackScholesPDE::leftBoundaryCond(double t) const
{
    double weight = option_->get_payoff()->left();
    double leftCond = (option_->get_k()) * exp(-(option_->get_r()) * ((option_->get_T() - t)));
    return weight * leftCond;
}

double BlackScholesPDE::rightBoundaryCond(double t, double x) const
{
    double weight = option_->get_payoff()->right()+x-x;
    double rightCond = option_->get_k() * exp(-(option_->get_r()) * ((t - option_->get_T())));
    return weight * rightCond;
}

double BlackScholesPDE::initCond(double x) const
{
    return option_->get_payoff()->operator()(x);
}

EurOption *BlackScholesPDE::get_option() const
{
    return option_;
}