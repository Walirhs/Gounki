/**
 * \file     jeton.h
 * \author    Mateus
 * \brief      La classe jeton qui peut contenir 3 pions max
 *
 * 
 *                 
 */

#ifndef JETON_H
#define	JETON_H
#include <iostream>
enum {VIDE=0,CARRE=1,ROND=2};
enum {DROITE=1,D_DROITE=2,AVANT=3,GAUCHE=4,D_GAUCHE=5,REBOND_C_GAUCHE=6,REBOND_C_DROITE=7,REBOND_R_GAUCHE=8,REBOND_R_DROITE=9};
///
///retourne le pion qu'il faut en fonction du deplacement
///
int quelPion(int direction);  

class Jeton{
public:
    ///
    ///construit le jeton avec le premeir pion à définir et a qui il appartient
    ///
    Jeton(const int premier_pion,const int joueur);
    ///
    ///constuit un pion vide(met toutes les variables à 0)
    ///
    Jeton();
    ///
    ///vide le jeton (met toutes les variables à 0)
    ///
    void videJeton();
    ///
    ///retourne le joueur 1 ou 2 du pion
    ///
    int getJoueur() ;
    ///
    ///retourne le nombre de pion empilé 
    ///
    int getNbPion() ;
    ///
    ///recupere le nombre de rond
    ///
    int getCarre() const;
    ///
    ///recupere le nombre de carre
    ///
    int getRond() const;
    ///
    ///on recupere le deplacment fait
    ///
    int getAncienDeplacement() const;
    ///
    ///on recupere le pion deplacé avant pour le cas des déploiements
    ///
    int getAncienPion() const;
    ///
    ///affecte des données au jeton
    ///
    void setJeton(const int joueur,const int nb_carre,const int nb_rond);
    ///
    ///met à jour l'ancien pion déplacé
    ///
    void setAncienPion(const int type_pion);
    ///
    ///met à jour l'ancien déplacement
    ///
    void setAncienDeplacement(const int direction);
    ///
    ///change la direction du rond a la direction opposé
    ///
    int rebondDirection(int direction);
    ///
    ///deploie les pions
    ///
    bool deploiement(Jeton &j,const int type_pion, int direction);
    ///
    ///empile les jeton ou le mange en fonction a qui appartient le pion 
    ///retourne false si ce n'est pas possible de le déplacer
    bool deplaceJeton(Jeton&, int type_pion,const int direction);
    ///
    ///on redefinie >> en un deplacement plus facile à voir 
    ///
    Jeton& operator >>(Jeton&);
    ///
    ///voit si le jeton contient le type de pion mis en parametre
    ///retroune cb il y en a
    ///
    int jeton_a_t_il(int type_pion) const;
    ///
    ///retounrne true si le jeton contient le pion mit en parametre
    ///
    bool jeton_a_t_il_bool(int type_pion) const;
    ///
    ///verifie si le deplacement demandé est légal
    ///
    bool deplacementLegal(int direction) const;
    ///
    ///fin du tour du joueur met 0 les anciens depalcements et pions déplacé
    ///
    void finTour();
    ///
    ///affiche juste les pions a l'interieur 
    ///
    void affiche() const;
    ///
    ///affiche toute les données de l'objet jeton
    ///
    void affiche(std::string ) const;
    ///
    //retourne le pion en string
    ///
    std::string affiche(int pion) const;
    
private:
    int tab_[3];
    int joueur_;
    int ancien_deplacement_;
    int ancien_pion_;
    int deploiement_;
};


#endif	/* JETON_H */

