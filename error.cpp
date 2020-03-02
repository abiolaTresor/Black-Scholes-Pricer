#include "error.h"
#include <fstream>
#include <cmath>

Error::Error(CrankNicholson *cr, FdmImplicite *p, int n)
{
    cr_ = cr;
    p_ = p;
    n_ = n;
}

void Error::compute() const
{
    ColMatrix c1 = cr_->get_curSol();
    std::vector<double> absc = cr_->get_xVect();
    std::vector<double> absc2 = p_->get_Correct_xVect();
    std::vector<double> c2 = p_->back_to_prices();
    if (cr_->get_pde()->get_option()->get_payoff()->right() == 1)
    {
        std::ofstream fdm_out("errorsCall.csv");
        for (int i = 1; i <= n_ - 2; i++)
        {
            if (abs(absc[i] - absc2[i] < 4))
            {
                fdm_out << absc[i] << " " << abs(c1[i] - c2[i]) << std::endl;
            }
        }
        fdm_out.close();
    }
    else
    {

        std::ofstream fdm_out("errorsPut.csv");
        for (int i = 1; i <= n_ - 2; i++)
        {
           if (abs(absc[i] - absc2[i] < 4))
            {
                fdm_out << absc[i] << " " << abs(c1[i] - c2[i]) << std::endl;
            }
        }
        fdm_out.close();
    }
}