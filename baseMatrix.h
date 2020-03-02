#ifndef BaseMatrix_
#define BaseMatrix_
#include <vector>
/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class BaseMatrix
  * \brief Représente une matrice
*/
class BaseMatrix {
protected:
int nl_;
int nc_;
public:
	/** 
     * \brief BaseMatrix
     * Contructeur de la classe BaseMatrix
     * \param int nl (resp nc) le nombre de lignes (resp nl)
    */ 
BaseMatrix(int nl, int nc);
	/** 
     * \brief BaseMatrix CC
     * Contructeur de copie de la classe BaseMatrix
     * \param BaseMatrix const& bM une matrice à copier
    */ 
BaseMatrix(BaseMatrix const& bM);
	/** 
     * \brief getters
     * \param
    */ 
double get_nl() const;
double get_nc() const;
virtual std::vector<double> get_data() const=0;
};
#endif