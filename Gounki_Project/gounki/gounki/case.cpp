#include <cstdlib>
#include <cassert>
#include "case.h"
#include "jeton.h"

Case::Case(){
    typeCase_=VIDE;
    jeton_=Jeton();
}
//permet de mettre a jour les données de la case
void Case::setTypeCase(int typeCase){
       typeCase_=typeCase; 
    }
//affiche le contenu de la case
void Case::affiche() const{
    jeton_.affiche();
}

//permet de recuperer le jeton
Jeton& Case::getJeton(){
    return jeton_;
}

bool Case::deplacement(Case& c,int type_pion, int direction){
    if(jeton_.deplaceJeton(c.getJeton(),type_pion,direction)==true)
        return true;
    return false;
}

//permet de savoir si la case est vide
bool Case::estVide() const{
    if(VIDE==typeCase_){
        return true;
    }
    return false;
}

int Case::getTypeCase() const {
    return typeCase_;
}

//permet de savoir si la case est une bordure
bool Case::estBordure() const{
    if (typeCase_==BORDURE){
       return true;
    }
    return false;
}

//permet de mettre a jour les donnÃ©es de la case
void Case::setCase(int type, Jeton& j){
    typeCase_=type;
    jeton_=j;
}