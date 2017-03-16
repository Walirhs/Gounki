
#include <cstdlib>
#include <cassert>
#include "jeton.h"
#include <iostream>
///
///construit le jeton pour premier parametre le premier pion qu on souhaite initialiser
///
Jeton::Jeton(const int premier_pion,const int joueur){
    assert(joueur==1 || joueur==2);
    assert(premier_pion >=0 && premier_pion <=3);
    joueur_=joueur;
    ancien_pion_=VIDE;
    ancien_deplacement_=VIDE;
    for(int i=0;i<3;i++){
        if(i==0)
            tab_[i]=premier_pion;
        else
            tab_[i]=0;
    }
    deploiement_=0;
}
///
/// construit un pion vide
///
Jeton::Jeton(){
    ancien_pion_=VIDE;
    joueur_=VIDE;
    ancien_deplacement_=VIDE;
    for(int i=0;i<3;i++){
            tab_[i]=VIDE;
    }
    deploiement_=0;
}
///
///vide le jeton
///
void Jeton::videJeton(){
    for(int i=0;i<3;i++)
         tab_[i]=0;
    joueur_=VIDE;
    ancien_deplacement_=VIDE;
    ancien_pion_=VIDE;
    deploiement_=0;
}
///
///retourne l'ancien deplacement fait
///
int Jeton::getAncienDeplacement() const{
    return ancien_deplacement_;
}

int Jeton::getAncienPion() const{
    return ancien_pion_;
}
///
///retourne le joueur 1 ou 2
///
int Jeton::getJoueur(){
    return joueur_;
}
///
///retourne le nombre de pion empilé
///
int Jeton::getNbPion(){
    return getCarre()+getRond();
}
///
///recupere le nombre de carre
///
int Jeton::getCarre() const{
    int somme=0;
    for(int i=0;i<3;++i){
        if(tab_[i]==CARRE){
            somme++;
        }
    }
    return somme;
}
///
///recupere le nombre de rond
///
int Jeton::getRond() const{
    int somme=0;
    for(int i=0;i<3;++i){
        if(tab_[i]==ROND){
            somme++;
        }
    }
    return somme;
}
///
///met à jour l'ancien pion déplacé
///
void Jeton::setAncienPion(const int type_pion){
    ancien_pion_ = type_pion;
}
///
///affecte des données au jeton
///
void Jeton::setJeton(int joueur, int nb_carre, int nb_rond){
    //assert(joueur==1 || joueur==2);
    assert(nb_carre+nb_rond<=3 && nb_carre+nb_rond>=0 );
    joueur_=joueur;
    ancien_deplacement_=0;
    ancien_pion_=0;
    int i;
    for(i=0;i<3;i++)
        tab_[i]=VIDE;
    for(i=0;i<nb_carre;i++){
        tab_[i]=CARRE;
    }
    for(;i<nb_carre+nb_rond;i++){
        tab_[i]=ROND;
    }
    deploiement_=0;
}
///
///met à jour l'ancien déplacement
///
void Jeton::setAncienDeplacement(const int direction){
    ancien_deplacement_=direction;
}
///
///on redefinie l'addition de deux jetons pour faciliter l'empillement des pions
///on présume qu'avant l'addition toutes les contraintes sont respecter
///
Jeton& Jeton::operator>>(Jeton &j){
    if(joueur_ != j.getJoueur()){//va le manger
        if(deploiement_==1){
             if(getAncienPion() == CARRE){
                j.setJeton(getJoueur(),getCarre()-1,getRond());
                setJeton(getJoueur(),getCarre()-1,getRond());
            }
            if(getAncienDeplacement() == ROND){
                j.setJeton(getJoueur(),getCarre(),getRond()-1); 
                setJeton(getJoueur(),getCarre(),getRond()-1);
            }
        }
        else
            j=*this;    
    }
    else//empile les jetons s'ils appratiennet au meme joueur
    {
        j.setJeton(getJoueur(),getCarre()+j.getCarre(),getRond()+j.getRond());
    }
    return j;
    
}
///
///deploiement laisse un pion sur la case et met le pion souhaiter sur l'autre case
///
bool Jeton::deploiement(Jeton& j,const int type_pion,const int direction){
    Jeton tmp;
    tmp=*this;
    int modifie=0;
    videJeton();
    
    joueur_=tmp.getJoueur();
    if(j.getJoueur()==tmp.joueur_ || j.getJoueur()==0){
        tab_[0]=tmp.getAncienPion();
        if(tmp.deploiement_==1){
            if(tmp.getAncienPion() == CARRE){
                j.setJeton(tmp.getJoueur(),tmp.getCarre()-1+j.getCarre(),tmp.getRond()+j.getRond());               
            }
            if(tmp.getAncienPion() == ROND){
                j.setJeton(tmp.getJoueur(),tmp.getCarre()+j.getCarre(),tmp.getRond()-1+j.getRond()); 
            }
            modifie++;
        }
        if(tmp.deploiement_==2){
            if(type_pion == CARRE){
                j.setJeton(tmp.getJoueur(),j.getCarre()+1,j.getRond());           
            }
            if(type_pion == ROND){
                j.setJeton(tmp.getJoueur(),j.getCarre(),j.getRond()+1);
            }
            modifie++;
        }
        if(tmp.deploiement_==0){
                j.setJeton(tmp.getJoueur(),tmp.getCarre()+j.getCarre(),tmp.getRond()+j.getRond());
                modifie++;
        }
        if(modifie==0)
        {
            j=*this; 
                
        }
       
    }
    else{
        if(j.getJoueur()!=tmp.joueur_ && ((tmp.deploiement_ == 1  && tmp.getNbPion() == 2 ) || (tmp.deploiement_==2 && tmp.getNbPion() == 2) || (tmp.deploiement_==0 && tmp.getNbPion() == 1))){
            tab_[0]=tmp.getAncienPion();
            if(tmp.deploiement_==1){
                if(tmp.getAncienPion() == CARRE){
                    j.setJeton(tmp.getJoueur(),tmp.getCarre()-1,tmp.getRond());               
                }
                if(tmp.getAncienPion() == ROND){
                    j.setJeton(tmp.getJoueur(),tmp.getCarre(),tmp.getRond()-1); 
                }
                modifie++;
            }
            if(tmp.deploiement_==2){
                if(tmp.getAncienPion() == CARRE){
                    j.setJeton(tmp.getJoueur(),tmp.getCarre()-1,tmp.getRond());
                }
                if(tmp.getAncienPion() == ROND){
                    j.setJeton(tmp.getJoueur(),tmp.getCarre(),tmp.getRond()-1); 
                }
                modifie++;

            }
            if(tmp.deploiement_==0) 
                j=tmp;
        }
        if(modifie==0){
            *this=tmp;
            return false;
        }   
    }
    j.setAncienPion(type_pion);
    j.setAncienDeplacement(direction);
    j.deploiement_=tmp.deploiement_+1;

    return true;
}
int Jeton::rebondDirection(int direction){ //change le rebond en une direction opposé 
    if(REBOND_R_GAUCHE==direction){
            setAncienDeplacement(D_DROITE);
        return D_DROITE;
    }
    if(REBOND_R_DROITE==direction){
            setAncienDeplacement(D_GAUCHE);
        return D_GAUCHE;
    }
    if(REBOND_C_GAUCHE==direction){
            setAncienDeplacement(DROITE);
        return DROITE;
    }
    if(REBOND_C_DROITE==direction){
            setAncienDeplacement(GAUCHE);
        return GAUCHE;
    }
    
}
//si je jeton est l'appartient alors il s'empile s'il le peut sinon return false
//si c'est un pion adversaire alors il le mange si son pion n'est pas en déploiement
bool Jeton::deplaceJeton(Jeton& j, int type_pion, int direction){
    if(deplacementLegal(direction)==false){//verifie si on peut si le deplacement correspond au deplacement du pion
        return false;
    }
    if(jeton_a_t_il(type_pion)==0){//verifie si jeton contient le pion souhaitant etre deplacé
        return false;
    }
    if(joueur_==j.getJoueur() && getNbPion()+j.getNbPion()>3 && deploiement_==0){//verifie s'il reste de la place dans l'autre pion ;
        return false;
    }
    if(ancien_pion_==ROND && type_pion==ROND && ancien_deplacement_!=direction && (direction==REBOND_R_GAUCHE || direction==REBOND_R_DROITE) ){
       direction= rebondDirection(direction); 
    }
    if(ancien_pion_==CARRE && type_pion==CARRE && ancien_deplacement_!=direction && (direction==REBOND_C_GAUCHE || direction==REBOND_C_DROITE) ){
       direction= rebondDirection(direction); 
    }
    if(ancien_deplacement_ == 0 || (ancien_deplacement_ == direction && getAncienPion()==type_pion) || (jeton_a_t_il(getAncienPion())==0 && ancien_deplacement_!=0 ) || (deploiement_!=0 && jeton_a_t_il(getAncienPion())<=1)){ //phase de deploiement verifie si le deplacement demander concondre au contrainte de deplacement d'un deploiement 
        deploiement(j,type_pion,direction);
        return true;
    }
    return false;
}

//fin du tour du joueur met 0 les anciens depalcements et pions déplacé
void Jeton::finTour(){
    ancien_pion_=VIDE;
    ancien_deplacement_=VIDE;
    deploiement_=0;
}   
//voit si le jeton d'un contient le type de pion mis en parametre
int Jeton::jeton_a_t_il(int type_pion) const{
    if(type_pion == CARRE){
        if(getCarre()>0)
            return getCarre();
    }    
    if(type_pion == ROND){
        if(getRond()>0)
            return getRond();
    }    
    return 0;
}

bool Jeton::jeton_a_t_il_bool(int type_pion) const{    
    if(type_pion == CARRE){
        if(getCarre()>0)
            return true;
    }    
    if(type_pion == ROND){
        if(getRond()>0)
            return true;
    }    
    return false;
}
//verifie si le deplacement demandé est légal
bool Jeton::deplacementLegal(int direction) const{
    if(quelPion(direction)==CARRE){
        if(jeton_a_t_il(CARRE)>0){
            return true;
        }
    }
    if(quelPion(direction)==ROND){
        if(jeton_a_t_il(ROND)>0){
            return true;
        }
    }
    return false;
}
//retourne 
std::string Jeton::affiche(int pion) const{
    if(CARRE == pion){
        if(joueur_ == 1)
            return "s";
        if(joueur_ == 2)
            return "S";
    }
    if(ROND == pion){
         if(joueur_ == 1)
            return "o";
        if(joueur_ == 2)
            return "O";
    }
    if(VIDE == pion){
        return " ";
    }
    std::cout<<"pion:"<<pion<<"!";
    return "$";
}
//affiche l'objet jeton
void Jeton::affiche() const{
    std::cout<<affiche(tab_[0])<<affiche(tab_[1])<<affiche(tab_[2]);
}
//affiche l'objet jeton
void Jeton::affiche(std::string jeton) const{
    std::cout<<"jeton "<<jeton<<std::endl;
    std::cout<<"pions: "<<affiche(tab_[0])<<affiche(tab_[1])<<affiche(tab_[2]);
    std::cout<<std::endl;
    std::cout<<"joueur: "<<joueur_<<std::endl;
    std::cout<<"ancien pion: "<<affiche(ancien_pion_)<<std::endl;
    std::cout<<"ancien deplacement: "<<ancien_deplacement_<<std::endl;
    std::cout<<"deploiement_:"<<deploiement_<<std::endl;
    std::cout<<std::endl;
}

//retourne le pion qu'il faut en fonction du deplacement
int quelPion(int direction){
    if(direction == DROITE || direction == AVANT ||direction == GAUCHE || direction == REBOND_C_GAUCHE || direction == REBOND_C_DROITE)
        return CARRE;
    if(direction == D_GAUCHE || direction == D_DROITE || direction == REBOND_R_GAUCHE || direction == REBOND_R_DROITE)
        return ROND;
    return VIDE;
}