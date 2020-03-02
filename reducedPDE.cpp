#include "reducedPDE.h"
#include <cmath>

ReducedPDE::ReducedPDE(EurOption *option)
{
    option_ = option;
    double r = option_->get_r();
    double sigma = option_->get_sigma();
    double k = r / (sigma * sigma / 2);
    alpha_ = -(k - 1) / 2;
    beta_ = -((k + 1) * (k + 1)) / 4;
}

double ReducedPDE::leftBoundaryCond(double t, double x) const
{
    double weight = option_->get_payoff()->left();
    double k = option_->get_k();
    double sigma = option_->get_sigma();
    double tt = option_->get_T() - (2 * t / (sigma * sigma));
    return weight*(1 / (k * exp(alpha_ * x + beta_ * t))) * k * exp(-(option_->get_r()) * ((option_->get_T() - tt)));
}

double ReducedPDE::rightBoundaryCond(double t, double x) const
{
    double weight = option_->get_payoff()->right();
    double k = option_->get_k();
    double sigma = option_->get_sigma();
    // double xx = k*exp(x);
    double tt = option_->get_T() - (2 * t / (sigma * sigma));
    return weight*(1 / (k * exp(alpha_ * x + beta_ * t))) * (k *exp(-(option_->get_r()) *(tt-option_->get_T())));
}

double ReducedPDE::initCond(double x) const{
    double k = option_->get_k();
    double xx = k*exp(x);
    return (1/(k*exp(alpha_*x)))*option_->get_payoff()->operator()(xx);
}

EurOption *ReducedPDE::get_option() const {
    return option_;
}

double ReducedPDE::get_alpha() const {
    return alpha_;
}

double ReducedPDE::get_beta() const {
    return beta_;
}
