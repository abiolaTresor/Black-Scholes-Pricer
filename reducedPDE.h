#ifndef reducedPDE_
#define reducedPDE_
#include "eurOption.h"

class ReducedPDE
{
private:
    EurOption *option_;
    double alpha_;
    double beta_;


public:
    ReducedPDE(EurOption *option);


    double leftBoundaryCond(double t, double x) const;
    double rightBoundaryCond(double t, double x) const;
    double initCond(double x) const;
    EurOption* get_option() const;
    double get_alpha() const;
    double get_beta() const;
};

#endif