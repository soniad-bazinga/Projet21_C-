#include "Amazone.hpp"

Amazone::Amazone()
{
    this->setHabilete(210);
    this->setSante(200);
}

int Amazone::attaquer(int choix, int armePoison) const
{
    switch (choix)
    {
    case 0: /*Arme*/
        if (armePoison != 0)
        {
            /*l'arme est empoisonnée*/
            cout <<"ARME EMPOISONNEE UTILISEE"<<endl;
            return -110;
        }
        else
        {   
            cout<<"ARME UTILISEE"<<endl; 
            return -60;
        }
    case 1: /*Bouclier*/
        cout<<"BOUCLIER UTILISEE"<<endl; 
        return 70;
    case 2: /*Poison*/
        cout<<"POISON UTILISE"<<endl;
        return -35;
    case 3: /*Medicament*/
        cout <<"MEDICAMENT UTILISE"<<endl; 
        return 45;
    /*AJOUTER LE CAS POUR LA CLÉ MAIS DOIT PLUTOT ETRE MISE DANS PERSONNAGE OU JOUEUR*/
    default:
        cout << "cas inconnu" << endl;
        return 0;
    }
}

char Amazone::initialePerso() const
{
    return 'a';
}