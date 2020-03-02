#ifndef TridiagoMatrix_
#define TridiagoMatrix_
#include "baseMatrix.h"
#include "colMatrix.h"
#include <vector>
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class TridiagoMatrix
  * \brief Représente une matrice tridiagonale
*/
class TridiagoMatrix : public BaseMatrix
{
private:
    std::vector<double> data_;
    double trash_ = 0;

public:
	/** 
     * \brief TridiagoMatrix
     * Contructeur de la classe TridiagoMatrix
     * \param Pas de paramètre (constructeur par défaut)
    */ 
    TridiagoMatrix();
    /** 
     * \brief TridiagoMatrix
     * setter
     * \param int nl, int nc, std::vector<double> data
    */ 
    TridiagoMatrix(int nl, int nc, std::vector<double> data);
    TridiagoMatrix(TridiagoMatrix const &tDM);
    double operator()(int i, int j) const;
    std::vector<double> get_data() const;
    double &operator()(int i, int j);
};

ColMatrix operator*(TridiagoMatrix const &tDM, ColMatrix const &cM);
#endif