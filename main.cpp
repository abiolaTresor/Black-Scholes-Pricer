#include "baseMatrix.h"
#include "blackScholesPDE.h"
#include "colMatrix.h"
#include "crankNicholson.h"
#include "eurOption.h"
#include "payoff.h"
#include "payoffCall.h"
#include "payoffPut.h"
#include "tridiagoMatrix.h"
#include "tridiagoLinearSolver.h"
#include "reducedPDE.h"
#include "fdmImplicite.h"
#include "error.h"
#include <iostream>

int main()
{
    try
    {
        // Creating the option parameters
        double K = 100;     // Strike price
        double r = 0.1;    // Risk-free rate 
        double sigma = 0.1; // Volatility of the underlying 
        double T = 1.0;    // One year until expiry

        // FDM discretisation parameters
        double borneX = 300.0; // Spot goes from [0.0, 300.0]
        int nIntX = 1000;
        double borneT = T; // Time period as for the option
        int nIntT = 1000;

        //creating the payoffCall and the option projects
        Payoff *pOffCall = new PayoffCall(K);
        EurOption *callOpt = new EurOption(pOffCall, K, r, T, sigma);

        //creating the PDE and the crankNichoson object
        BlackScholesPDE *pde = new BlackScholesPDE(callOpt);
        CrankNicholson cNchlsn(pde, borneX, nIntX, borneT, nIntT);
        //running the cranknichloson solver
        cNchlsn.execute();

        // //creating the payoffPut and the option projects
        Payoff *pOffPut = new PayoffPut(K);
        EurOption *putOpt = new EurOption(pOffPut, K, r, T, sigma);

        //creating the PDE and the crankNichoson object
        BlackScholesPDE *pde2 = new BlackScholesPDE(putOpt);
        CrankNicholson cNchlsn2(pde2, borneX, nIntX, borneT, nIntT);
        //running the cranknichloson solver
        cNchlsn2.execute();

        //creating reduced PDE and the fdmImplicite object
        ReducedPDE* pde3 = new ReducedPDE(callOpt);
        FdmImplicite fdm (pde3, borneX, nIntX, borneT, nIntT);
        //running the fdm solver
        fdm.execute();
        
        //creating reduced PDE and fdmImplicite object
        ReducedPDE* pde4 = new ReducedPDE(putOpt);
        FdmImplicite fdm2 (pde4, borneX, nIntX, borneT, nIntT);
        fdm2.execute();

        //computing errors for Call
        Error erCall(&cNchlsn,&fdm,nIntX);
        erCall.compute();

        //computing errors for Put
        Error erPut(&cNchlsn2,&fdm2,nIntX);
        erPut.compute();

        //freeing memories allocated
        delete(pOffCall);
        delete(callOpt);
        delete(pde);
        delete(pOffPut);
        delete(putOpt);
        delete(pde2);
        delete(pde3);
        delete(pde4);
    }
    catch (const char *str)
    {
        std::cout << str << std::endl;
    }

    return 0;
}
