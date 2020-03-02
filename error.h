#ifndef Error_
#define Error_
#include "crankNicholson.h"
#include "fdmImplicite.h"

/**
* @author Abiola Trésor Djigui
*/

/** 
  * \class CrankNicholson 
  * \brief Représente la méthode de CrankNicholson.
*/
class Error
{
    CrankNicholson *cr_;
    FdmImplicite *p_;
    int n_;

public:
    /** 
     * \brief Error
     * Contructeur de la classe Error
     * \param CrankNicholson*, FdmImplicite*
    */
    Error(CrankNicholson *cr, FdmImplicite *p, int n);

    /** 
     * \brief compute
     * méthode pour mettre en place le fichier des erreurs
     * \param CrankNicholson*, FdmImplicite*
    */
    void compute() const;
};
#endif