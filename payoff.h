#ifndef PAYOFF_
#define PAYOFF_

#include<algorithm>

/** 
 * \file    payoff.h
 * \brief   contient une classe virtuelle représentant la fonctionnalité du payoff
 * \author  DJIGUI Trésor
*/



/** 
  * \class Payoff
  * \brief Représente la fonctionnalité du payoff
*/

class Payoff
{
public:
    /** 
     * \brief Contructor
     * Contructor of class Payoff
     * \param No parameter (default constructor)
    */
    Payoff();

    /** 
     * 
    */
    virtual ~Payoff(){};

    /** 
     * \brief Overloded operator()
     * 
    */
    virtual double operator()(double const &s) const = 0;

    virtual double left() const = 0;
    virtual double right() const = 0;
};

#endif