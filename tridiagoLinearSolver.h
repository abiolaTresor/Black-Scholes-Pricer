#ifndef TridiagoLinearSolver_
#define TridiagoLinearSolver_
#include "tridiagoMatrix.h"
#include "colMatrix.h"
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class TridiagoLinearSolver
  * \brief Représente un solveur pour matrice tridiagonales
*/
class TridiagoLinearSolver {
    private:
    TridiagoMatrix* tdM_;
    ColMatrix* cM_;

    public:
    /** 
     * \brief TridiagoLinearSolver
     * Contructeur de la classe TridiagoLinearSolver
     * \param 
    */ 
    TridiagoLinearSolver(TridiagoMatrix* tdM, ColMatrix *cM);
    ColMatrix solve() const;
};

#endif