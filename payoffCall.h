#ifndef PayoffCall_
#define PayoffCall_

#include "payoff.h"
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class PayoffCall
  * \brief Représente le payoff d'un call
*/
class PayoffCall : public Payoff
{
private:
    double k_;

public:
	/** 
     * \brief PayoffCall
     * Contructeur de la classe PayoffCall
     * \param 
    */  
    PayoffCall(double const& K_);
    /** 
     * \brief Destructeurde la classe payoffCall
    */
    virtual ~PayoffCall(){};
    double operator() (double const& s) const;
    double left() const;
    double right() const;
};
#endif