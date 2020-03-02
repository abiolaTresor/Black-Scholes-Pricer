#include "baseMatrix.h"

BaseMatrix::BaseMatrix(int nl, int nc){
    nl_=nl;
    nc_=nc;
}

BaseMatrix::BaseMatrix(BaseMatrix const& bM){
    nl_=bM.get_nl();
    nc_=bM.get_nc();
}
double BaseMatrix::get_nl() const{
    return nl_;
}


double BaseMatrix::get_nc() const{
    return nc_;
}