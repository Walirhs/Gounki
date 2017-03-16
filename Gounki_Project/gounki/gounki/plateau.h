/**
 * \file      plateau.h
 * \author    Mateus & Gouloi
 * 
 * \brief      La classe plateau au bon fonctionnement du jeu
 *
 * 
 *                 
 */

#include "case.h"
#ifndef PLATEAU_H
#define	PLATEAU_H

class Plateau {
public:
    ///
    ///construit le plateau
    ///
    Plateau();
    ///
    ///affiche le plateau
    ///
    void affiche() const;
    ///
    ///savoir quel pion on deplace
    ///
    int quelPionDeplace(const Case c,const int direction) const;
    ///
    ///permet de savoir la direction du pion déplacé
    ///
    int quelleDirection(int l1,int c1,int l2,int c2)  const;
    ///
    ///fonction qui verifie que la commande saisie repond a toute les contrainte du jeu
    ///
    ///
    ///sinon return false s'il y a pas un des contraintes remplies
    ///
    bool autoriseCommande(int taille_commande, int s[]) const;
    ///
    ///regarde si le pion deplacé correspond au pion appartient bien au joueur
    ///
    bool deplacementLegal(Case c) const;
    ///
    ///prend les commandes de l'utilasateur 
    ///
    void commande();
    ///
    ///deplacement de pion
    ///
    bool deplacement();
    ///
    ///retourne le gagnant sinon 0
    ///
    int gagnant() ;
    ///
    ///Met tous les valeurs ancien valeurs à 0
    ///
    void finTour();
    ///
    ///remet tout a zero, on recommence le jeu
    ///
    void reset();
    ///
    ///permet de recuperer la commande faite
    ///
    std::string getCommande() const;
    ///
    ///commande help, affche des emplacement qui pourait aider le joueur 
    ///
    void help() const;
private:
    int joueur_courant_;
    std::string commande_;
    Case p[10][10];
};

#endif	/* PLATEAU_H */
///
///les saisie des commandes de l'utilisateur seront en string
///
///
///on devra donc convertir les commandes en coordonnées (pour le tableau)
///
///
///int convertirCommande(std::string commande);
///