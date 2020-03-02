#include "eurOption.h"

EurOption::EurOption() {}

EurOption::EurOption(Payoff *payoff, double k, double r, double t, double sigma)
{
    payoff_ = payoff;
    k_ = k;
    r_ = r;
    T_ = t;
    sigma_ = sigma;
}

double EurOption::get_k() const {
    return k_;
}

double EurOption::get_r() const {
    return r_;
}

double EurOption::get_T() const {
    return T_;
} 

double EurOption::get_sigma() const {
    return sigma_;
}

Payoff* EurOption::get_payoff() const {
    return payoff_;
}
