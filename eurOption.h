#ifndef EurOption_
#define EurOption_

#include "payoff.h"
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class EurOption
  * \brief Représente une Option européenne
*/
class EurOption
{
private:
    Payoff *payoff_;
    double k_;
    double r_;
    double T_;
    double sigma_;

public:
    /** 
     * \brief EurOption
     * Contructeur de la classe EurOption
     * \param Pas de paramètre (constructeur par défaut)
    */
    EurOption();
    /** 
     * \brief EurOption
     * setter
     * \param Payoff *payoff le payoff, double k, double r le taux d'intérêt du marché, double t el temps, double sigma la volatilité de l'actif
    */
    EurOption(Payoff *payoff, double k, double r, double t, double sigma);
    /** 
     * \brief getters
     * \param
    */ 
    Payoff *get_payoff() const;
    double get_k() const;
    double get_r() const;
    double get_T() const;
    double get_sigma() const;
};

#endif