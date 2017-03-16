/**
 * \file       case.h
 * \author    Goulou
 * 
 * \brief      La classe case qui contient un jeton et un type 
 *
 * 
 *                 
 */

#include "jeton.h"

#ifndef CASE_H
#define	CASE_H
enum {OCCUPEE=1,BORDURE=2,ARRIVEE=3};
class Case{
public:
    ///
    ///constucteur vide pour utiliser la clas en tableau
    ///
    Case();
    ///
    ///permet de savoir si la case est vide
    ///
    bool estVide() const;
    ///
    ///permet de savoir si la case est une bordure
    ///
    bool estBordure() const;
    ///
    ///permet de recuperer le jeton
    ///
    Jeton& getJeton();
    ///
    ///permet de mettre a jour les données de la case
    ///
    void setTypeCase(int type);
    ///
    ///met a jour la case
    ///
    void setCase(int type, Jeton& j);
    ///
    ///vide la case
    ///
    void viderCase();
    ///
    ///recuper le type de la case
    ///
    int getTypeCase() const;
    ///
    ///déplace les jetons contenus dans la case mise en paramètre
    ///
    bool deplacement(Case& c,int type_pion, int direction);
    ///
    ///affiche le contenu de la case
    ///
    void affiche() const;
    
private:
    
    ///
    ///correspond a la valeur de la case
    ///
    int typeCase_;
    Jeton jeton_;
};


#endif	/* CASE_H */


