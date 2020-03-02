#ifndef FdmImplicite_
#define FdmImplicite_
#include "reducedPDE.h"
#include "tridiagoMatrix.h"
#include "colMatrix.h"
#include <vector>
/** 
  * \class FdmImplicite
  * \brief Représente la méthode des différences finies implicite
  */
class FdmImplicite
{
private:
  ReducedPDE *pde_;

  //sur l'espace
  double borneInfX_;
  double borneSupX_;
  int nIntX_;
  double dX_;
  std::vector<double> xVect_;

  //sur le temps
  double borneSupT_;
  int nIntT_;
  double dT_;
  std::vector<double> tVect_;

  //matrice d'itérations
  TridiagoMatrix C_;

  //info d'itérations
  int i_ = 0;
  ColMatrix curInnerSol_;

  //methode privée de mise à jour des frontières
  TridiagoMatrix compute_C();
  void set_curInnerSOl();
  double a_i();
  double b_i();
  double c_i();

  //méthode privée de conversion finale
  std::vector<double> back_to_prices(ColMatrix *cM) const;

public:
  /** 
     * \brief Contructeur
     * Contructeur de la classe FdmImplicite
     * \param ReducedPDE *pde l'équation réduite, double borneX, int lengthX, double borneT, int lengthT
    */
  FdmImplicite(ReducedPDE *pde, double borneX, int lengthX, double borneT, int lengthT);

  /** 
     * getteurs la classe FdmImplicite
    */
  std::vector<double> get_xVect() const;
  std::vector<double> get_Correct_xVect() const;
  std::vector<double> get_tVect() const;
  ReducedPDE* get_pde() const;

  /** 
     * \brief back_to_prices
     * convertis en vrais prix
    */
  std::vector<double> back_to_prices() ;

  /** 
     * \brief execute
     * résous via la fdm implicite
    */
  void execute();
};

#endif