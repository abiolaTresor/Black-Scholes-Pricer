#ifndef blackScholesPDE_
#define blackScholesPDE_
#include "eurOption.h"
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class blackScholesPDE
  * \brief Représente l'équation différentielle d'une équation de blackScholes
*/
class BlackScholesPDE
{
private:
    EurOption *option_;

public:
    /** 
     * \brief blackScholesPDE
     * Contructeur de la classe backScholesPDE
     * \param EurOption *option une option
    */ 
    BlackScholesPDE(EurOption *option);
    /** 
     * \brief leftBoundaryCond
     * renvoie la condition à gauche
     * \param double t, double x
    */ 
    double leftBoundaryCond(double t) const;
    /** 
     * \brief rightBoundaryCond
     * renvoie la condition à droite
     * \param double t, double x
    */ 
    double rightBoundaryCond(double t, double x) const;
    /** 
     * \brief initCond
     * renvoie la condition initiale
     * \param double x
    */ 
    double initCond(double x) const;
    EurOption *get_option() const;
};

#endif