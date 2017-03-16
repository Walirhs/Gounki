/**
 * \file          main.c
 * \author    Mateus && Goulou
 * 
 * 
 * \brief      Le déroulement du jeu
 *
 * 
 *                 
 */

#include <cstdlib>
#include "jeton.h"
#include "case.h"
#include "plateau.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Plateau p;
    p.affiche();
    std::cout<<std::endl;
    int gagnant =p.gagnant();
    
    while(gagnant==0){
      gagnant = p.gagnant();
      if(gagnant == 0)
        p.deplacement();
      if(p.getCommande()=="help")
          p.help();
    }
        
    std::cout<<"le gagnant est le joueur: "<<p.gagnant()<<std::endl;
    p.affiche();
    
    return 0;
}

