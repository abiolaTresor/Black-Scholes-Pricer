#include "payoffCall.h"

PayoffCall::PayoffCall(double const& k){
    k_=k;
}

double PayoffCall::operator() (double const& s) const {
  return std::max(s-k_, 0.0); 
}

double PayoffCall::left() const{
  return 0.0;
}

double PayoffCall::right() const{
  return 1.0;
}

