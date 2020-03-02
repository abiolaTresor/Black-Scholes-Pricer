#ifndef PayoffPut_
#define PayoffPut_

#include "payoff.h"
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class PayoffPut
  * \brief Représente le payoff d'un put
*/
class PayoffPut : public Payoff
{
private:
    double k_;

public:
	/** 
     * \brief PayoffPut
     * Contructeur de la classe PayoffPut
     * \param 
    */
    PayoffPut(double const& K_);
    /** 
     * \brief Destructeurde la classe payoffPut
    */
    virtual ~PayoffPut(){};
    virtual double operator() (double const& s) const;

    double left() const;
    double right() const;
};
#endif