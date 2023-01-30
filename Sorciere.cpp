#include "Sorciere.hpp"

Sorciere::Sorciere()
{
    this->setHabilete(150);
    this->setSante(200);
}

int Sorciere::attaquer(int choix, int armePoison) const
{
    switch (choix)
    {
    case 0: /*Arme*/
        if (armePoison != 0)
        {
            /*l'arme est empoisonnée*/
            cout << "ARME EMPOISONNEE UTILISEE" << endl;
            return -70;
        }
        else
        {
            cout << "ARME UTILISEE" << endl;
            return -50;
        }
    case 1: /*Bouclier*/
        cout << "BOUCLIER UTILISE" << endl;
        return 30;
    case 2: /*Poison*/
        cout << "POISON UTILISE" << endl;
        return -110;
    case 3: /*Medicament*/
        cout << "MEDICAMENT UTILISE" << endl;
        return 80;
    /*AJOUTER LE CAS POUR LA CLÉ MAIS DOIT PLUTOT ETRE MISE DANS PERSONNAGE OU JOUEUR*/
    default:
        cout << "cas inconnu" << endl;
        return 0;
    }
}

char Sorciere::initialePerso() const
{
    return 's';
}