#include <cstdlib>
#include <cassert>
#include "case.h"
#include <iostream>
#include "jeton.h"
#include "plateau.h"
#include <cstring>

Plateau::Plateau(){
    int reste=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            p[i][j]=Case();
        }
    }
    for(int i=0;i<10;i++){
        p[i][0].setTypeCase(BORDURE);
    }
    for(int i=0;i<10;i++){
        p[i][9].setTypeCase(BORDURE);
    }
    for(int i=0;i<10;i++){
        p[0][i].setTypeCase(ARRIVEE);
    }
    for(int i=0;i<10;i++){
        p[9][i].setTypeCase(ARRIVEE);
    }
    for(int i=1;i<=2;i++){
        for(int j=1;j<=8;j++){
            p[i][j].setTypeCase(1);
            if(j%2==reste){
                p[i][j].getJeton().setJeton(1,1,0);
            }
            else{
                p[i][j].getJeton().setJeton(1,0,1);
            }
        }
        reste++;
    }
    reste=0;
    for(int i=7;i<=8;i++){
        for(int j=1;j<=8;j++){
            p[i][j].setTypeCase(1);
            if(j%2==reste)
                p[i][j].getJeton().setJeton(2,1,0);
            else
                p[i][j].getJeton().setJeton(2,0,1);
        }
        reste++;
    }
    commande_=" ";
    joueur_courant_=1;
}

//Met tous les valeurs ancien valeurs à 0
void Plateau::finTour(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            p[i][j].getJeton().finTour();
        }
    }
    if(joueur_courant_==1)
        joueur_courant_=2;
    else
        joueur_courant_=1;
}

bool Plateau::autoriseCommande(int taille_commande, int s[]) const { 
    int direction,pion;
    bool deplacement;
    for(int i=0;i<=taille_commande-4;i=i+2)
    {     
        direction = quelleDirection(s[1+i],s[0+i],s[3+i],s[2+i]);
        pion = quelPionDeplace(p[s[1]][s[0]],direction);
        deplacement=deplacementLegal(p[s[1]][s[0]]);
        
        if(pion == 0 || deplacement == false || direction == 0 )
            return false;
    }
    return true;
}

bool Plateau::deplacementLegal(Case c) const{
    if(joueur_courant_ == c.getJeton().getJoueur())
        return true;
    return false;
}

int Plateau::quelPionDeplace(Case c,int direction) const{
    int pion = quelPion(direction);
    Jeton j =  c.getJeton();
    bool A_le_pion = j.jeton_a_t_il_bool(pion);
    if(pion==VIDE)
        return VIDE;
    if(A_le_pion==true)
        return pion;
    return VIDE;
}

int Plateau::quelleDirection(int l1,int c1,int l2,int c2) const{
     std::cout<<true<<std::endl;
    if(l1==l2){//depalcement gauche droite
        if(c1-1==c2)
            return GAUCHE;
        if(c1+1==c2)
            return DROITE;
    }
    if(joueur_courant_==2){

        if(c1==c2){//depalcement avant
            if(l1==l2+1)
                return AVANT;
        }
        if(l1-1==l2){//depalcement en digonale 
            if(c1==c2+1){
                if(p[l1][c1+1].estBordure()==true)
                    return REBOND_R_DROITE;                
                else
                    return D_GAUCHE;
            }
                
            if(c1==c2-1){
                if(p[l1][c1-1].estBordure()==true)
                    return REBOND_R_GAUCHE;
                else
                    return D_DROITE;
            }
                
        }

    }
    if(joueur_courant_==1){
        if(c1==c2){//depalcement avant
            if(l1+1==l2)
                return AVANT;
        }
        if(l1+1==l2){//depalcement en digonale 
            if(c1+1==c2){
                if(p[l1][c1-1].estBordure()==true)
                    return REBOND_R_GAUCHE;
                else
                    return D_DROITE;
            }
                
            if(c1-1==c2){
               if(p[l1][c1+1].estBordure()==true)
                    return REBOND_R_DROITE; 
               else
                    return D_GAUCHE; 
            }
        }
    }
    if(c1==c2 && l1==l2){//le rebond du carre, le sens du rebond est indépendant du joueur 
        if(p[l1][c1-1].estBordure())
            return REBOND_C_GAUCHE;
        if(p[l1][c1+1].estBordure())
            return REBOND_C_DROITE;
    }

    return VIDE;
}

bool Plateau::deplacement(){
    int jouer=0;
    do
    {
        if(gagnant()!=0)
            return false;
        commande();
        
        if(commande_=="help")
            return false;
        unsigned long long value = atoi(commande_.c_str());//transforme la chaine de caractere en un chiffre
        
        
        int s[commande_.size()];//crÃ©ation d'un tableau de la taille de la commande
        for (int i=commande_.size()-1; i >=0; i--) {//met chaque chiffre par case du nimbre 
            s[i] = value % 10;
            value /= 10;
        }
        std::cout<<std::endl;
        for(int i=0;i<commande_.size();i++)
            std::cout<<s[i]<<std::endl;
        //fonction qui recupere le nombre de pion sur les pions sur la case qu'on souhaite bouge 
        //comme ca s'il y a erreur apres pour que le joueur puisse continuer à deploiyer 
        int pion,direction;    
        if(autoriseCommande(commande_.size(),s)==true)
        {
            if(gagnant()!=0)
               return false;
            for(int i=0;i<=commande_.size()-4;i=i+2){    
                direction = quelleDirection(s[1+i],s[0+i],s[3+i],s[2+i]);
                pion = quelPionDeplace(p[s[1+i]][s[0+i]],direction);

    
                 //mettre un if sur direction si elle correspond a rebond  et tester si la case a droite ou a gauche est une case de type bordure 
                //apres on change l'ancienne direction et on la met du sens opposé au rebond
                if(!p[s[1+i]][s[0+i]].deplacement(p[s[3+i]][s[2+i]],pion,direction))
                    std::cout<<"Introduire fonction qui recupere commande i-2"<<std::endl;

                affiche();
                
                if(gagnant()!=0)
                   return false;
                
            }
            finTour();
            jouer++;
            

        }
        else {
            affiche();
            std::cout<<"pas de deplacement possible, recommencez !"<<std::endl;
        }  
    
    }while(jouer==0);

    return true;
}

void Plateau::affiche() const{
    int k=9;
    std::cout<<"   0";
    for(char i='a';i<='h';i++)
        std::cout<<"   "<<i;
    std::cout<<"   9";
    std::cout<<std::endl;
    std::cout<<" ";
    for(int i=0;i<10;i++)
        std::cout<<"+---";
    std::cout<<"+";
    std::cout<<std::endl;
    for(int i=0;i<10;i++){
        std::cout<<k--<<"|";
        for(int j=0;j<10;j++){
            p[i][j].affiche();
            std::cout<<"|";
        }
        std::cout<<std::endl;
        std::cout<<" ";
        for(int i=0;i<10;i++)
        std::cout<<"+---";
        std::cout<<"+";
        std::cout<<std::endl;
    }
        
}

int Plateau::gagnant()  {
    int cmpt=0;
    //si le joueur arrive a la ligne d arrivee
    for(int i=1; i<=8; i++){
        if(p[0][i].getJeton().getJoueur()==joueur_courant_ || p[i][9].getJeton().getJoueur()==joueur_courant_)
            return joueur_courant_;
    }
    //si un de s joueur n'as plus de pion
    for(int i=1; i<=8; i++){
        for(int j=1; j<=8; j++){
            if(p[i][j].getJeton().getJoueur()==joueur_courant_)
                cmpt++;
        }
    }
    if(cmpt==0)
        return joueur_courant_;
        
    return 0;
}

void Plateau::help() const {
//    if(joueur_courant_==2){
//        int nb_pion;
//        
//        int help=0;
//        for(int i=1;i<=8 && help == 0;i++){
//            for(int j=1;i<=8;i++){
//                //if(p[i][j].getJeton().getJoueur()==joueur_courant_){
//                //    help++;
//                    
//                }
//            }
//        }
//    }
    std::cout<<"Pour avoir de l'aide contacter moi par email (manque de temps)"<<std::endl;
}

std::string Plateau::getCommande() const{
    return commande_;
}

void Plateau::commande()
 {
    int reset; 
    std::string maChaine;
    reset=0; 
    std::cout<<"Pour jouer vous devez saisir d'abord la lettre puis le chiffre, les enchainements de saisie se fait sans espace ex: b8a7c6d5 pour un deploiememt de 3 pions"<<std::endl;  
    std::cout<<"Au joueur "<<joueur_courant_<<" de jouer"<<std::endl;  
    getline(std::cin, maChaine);
    std::size_t found = maChaine.find("help");
    if (found!=std::string::npos)
        commande_="help";
    else 
        commande_=maChaine;
 
    if(commande_!="help"){
        for(int i=0;i<maChaine.size();i=i+2)
        {
            switch(maChaine[i])
            {
                case'a':maChaine[i]='1';
                break;
                case'b':maChaine[i]='2';
                break;
                case'c':maChaine[i]='3';
                break;
                case'd':maChaine[i]='4';
                break;
                case'e':maChaine[i]='5';
                break;                                                   
                case'f':maChaine[i]='6';     
                break;
                case'g':maChaine[i]='7';
                break;
                case'h':maChaine[i]='8';
                break;
            }   
            switch(maChaine[i+1])
            {
                case'9':maChaine[i+1]='0';
                break;
                case'8':maChaine[i+1]='1';
                break;
                case'7':maChaine[i+1]='2';
                break;
                case'6':maChaine[i+1]='3';
                break;
                case'5':maChaine[i+1]='4';
                break;
                case'4':maChaine[i+1]='5';
                break;                                                   
                case'3':maChaine[i+1]='6';     
                break;
                case'2':maChaine[i+1]='7';
                break;
                case'1':maChaine[i+1]='8';
                break;
                case'0':maChaine[i+1]='9';
                break;
            }
        } 
        std::cout<<maChaine<<std::endl;
        commande_= maChaine;
    }
    	 
}