#include "Piece.hpp"

bool Piece::estConnectee(Piece *p)
{
    return this->nord && p->sud || this->est && p->ouest || this->sud && p->nord || this->ouest && p->est;
};

string Piece::save(){
    string json = string("[")+to_string(nord)+string(",")+to_string(est)+string(",")+to_string(sud)+string(",")+to_string(ouest)+string("]");
    return json;
};

Meuble* Piece::chercherObjet(char ini){
        switch (ini)
        {
        case 'a':
            /*on cherche une arme*/
            for (Meuble *meu : decoration)
            {
                if (meu->obj == Meuble::Objet::Arme)
                {
                    return meu;
                }
            }
            break;
        case 'p':
            /*on cherche un poison*/
            for (Meuble *meu : decoration)
            {
                if (meu->obj == Meuble::Objet::Poison)
                {
                    return meu;
                }
            }
            break;
        case 'm':
            /*on cherche un medoc*/
            for (Meuble *meu : decoration)
            {
                if (meu->obj == Meuble::Objet::Medicament)
                {
                    return meu;
                }
            }
            break;
        case 'c':
            /*on cherche une clé*/
            for (Meuble *meu : decoration)
            {
                if (meu->obj == Meuble::Objet::Cle)
                {
                    return meu;
                }
            }
            break;
        case 'b':
            /*on cherche un bouclier*/
            for (Meuble *meu : decoration)
            {
                if (meu->obj == Meuble::Objet::Bouclier)
                {
                    return meu;
                }
            }
            break;
        }
        return nullptr;
}

void Piece::addPerso(Personnage *p) 
{
    roommates.push_back(p);
};

void Piece::addObj(Meuble *o) 
{
    decoration.push_back(o);
};

bool Piece::contientClef(){
    for (int i=0; i<decoration.size(); i++){
        if(decoration[i]->estClef()){
            return 1;
        }
    }
    return 0;
};

bool Piece::contientArme(){
    for (int i=0; i<decoration.size(); i++){
        if(decoration[i]->estArme()){
            return 1;
        }
    }
    return 0;
};

bool Piece::contientBouclier(){
    for (int i=0; i<decoration.size(); i++){
        if(decoration[i]->estBouclier()){
            return 1;
        }
    }
    return 0;
};

bool Piece::contientPoison(){
    for (int i=0; i<decoration.size(); i++){
        if(decoration[i]->estPoison()){
            return 1;
        }
    }
    return 0;
};

bool Piece::contientMedicament(){
    for (int i=0; i<decoration.size(); i++){
        if(decoration[i]->estMedicament()){
            return 1;
        }
    }
    return 0;
};

string Piece::listePerso(){
    string ret ="";
    for (int i=0; i<roommates.size(); i++){
        ret = ret + roommates[i]->initialePerso();
    }
    return ret;
};

void Piece::erase(int k){
    roommates.erase(roommates.begin()+k);
}

void Piece::supprime(Meuble *o){
    for(int i=0;i<decoration.size();i++){
        if(decoration[i]->estMedicament() && o->estMedicament()){
            decoration.erase(decoration.begin() + i);
            return;
        }
        if (decoration[i]->estBouclier() && o->estBouclier()){
            decoration.erase(decoration.begin() + i);
            return;
        }
        if (decoration[i]->estClef() && o->estClef()){
            decoration.erase(decoration.begin() + i);
            return;
        }
        if (decoration[i]->estPoison() && o->estPoison()){
            decoration.erase(decoration.begin() + i);
            return;
        }
        if (decoration[i]->estArme() && o->estArme()){
            decoration.erase(decoration.begin() + i);
            return;
        }
    }
}
