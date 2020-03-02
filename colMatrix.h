#ifndef ColMatrix_
#define ColMatrix_
#include "baseMatrix.h"
#include <vector>
/** 
  * \class ColMatrix
  * \brief Représente une matrice colonne.
*/
class ColMatrix : public  BaseMatrix {
    private:
    std::vector<double> data_;
    public:
    /** 
     * \brief Contructeur
     * Contructeur de la classe ColMatrix (initialise un vecteur de taille (1,1) )
     * \param Pas de paramètre (constructeur par défaut)
    */   
    ColMatrix();
    /** 
     * \brief ColMatrix 
     * permet d'initialiser un vecteur colonne
     * \param int nl le nombre de lignes, std::vector<double> data
    */ 
    ColMatrix(int nl, std::vector<double> data);
    /** 
     * \brief ColMatrix 
     * permet de convertir un vecteur BaseMatrix en ColMatrix
     * \param BaseMatrix const& bM, std::vector<double> data
    */  
    ColMatrix(BaseMatrix const& bM, std::vector<double> data);
    /** 
     * \brief ColMatrix 
     
     * \param int nl le nombre de lignes, std::vector<double> data
    */  
    ColMatrix(ColMatrix const & tDM);
    double operator[](int i) const;
    double& operator[](int i);
    std::vector<double> get_data() const;
    

};

ColMatrix operator*(double d, ColMatrix const& cM);
ColMatrix operator+(ColMatrix const& cM1, ColMatrix const& cM2);

#endif