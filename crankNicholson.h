#ifndef CrankNicholson_
#define CrankNicholson_
#include "blackScholesPDE.h"
#include "tridiagoMatrix.h"
#include "colMatrix.h"
#include <vector>
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class CrankNicholson 
  * \brief Représente la méthode de CrankNicholson.
*/
class CrankNicholson
{
private:
    BlackScholesPDE *pde_;

    //sur l'espace
    double borneX_;
    int nIntX_;
    double dX_;
    std::vector<double> xVect_;

    //sur le temps
    double borneT_;
    int nIntT_;
    double dT_;
    std::vector<double> tVect_;

    //matrices de résolution
    TridiagoMatrix C_;
    TridiagoMatrix D_;

    //info d'itérations
    int i_ = 0;
    ColMatrix prevInnerSol_;
    ColMatrix curInnerSol_;
    ColMatrix prevBoundaries_;
    ColMatrix curBoundaries_;

    //methode privée de mise à jour des frontières
    void updateBoundaries();
    TridiagoMatrix compute_C();
    TridiagoMatrix compute_D();
    void set_prevAndCurInnerSOl();
    void set_prevAndCurBoundaries();
    double a_i(int i);
    double b_i(int i);
    double c_i(int i);



public:
    /** 
     * \brief CrankNicholson
     * Contructeur de la classe CrankNicholson
     * \param 
    */ 
    CrankNicholson(BlackScholesPDE *pde, double borneX, int lengthX, double borneT, int lengthT);
    /** 
     * \brief getters
     * \param
    */ 
    std::vector<double> get_xVect() const;
    std::vector<double> get_tVect() const;
    ColMatrix get_curSol() const;
    BlackScholesPDE* get_pde() const;
    
    void execute();
};

#endif