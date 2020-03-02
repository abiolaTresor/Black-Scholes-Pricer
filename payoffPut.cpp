#include "payoffPut.h"

PayoffPut::PayoffPut(double const& k){
    k_=k;
}


double PayoffPut::operator() (double const& s) const {
  return std::max(k_-s, 0.0); 
}

double PayoffPut::left() const{
  return 1.0;
}

double PayoffPut::right() const{
  return 0.0;
}