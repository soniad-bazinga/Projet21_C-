#include "Moine.hpp"

Moine::Moine()
{
    this->setSante(250);
    this->setHabilete(100);
}

int Moine::attaquer(int choix, int armePoison) const
{
    switch (choix)
    {
    case 0: /*Arme*/
        if (armePoison != 0)
        {
            /*l'arme est empoisonnée*/
            cout << "ARME EMPOISONNEE UTILISEE" << endl;
            return -40;
        }
        else
        {
            cout << "ARME UTILISEE" << endl;
            return -25;
        }
    case 1: /*Bouclier*/
        cout << "BOUCLIER UTILISE" << endl;
        return 35;
    case 2: /*Poison*/
        cout << "POISON UTILISE" << endl;
        return -30;
    case 3: /*Medicament*/
        cout << "MEDICAMENT UTILISE" << endl;
        return 110;
    /*AJOUTER LE CAS POUR LA CLÉ MAIS DOIT PLUTOT ETRE MISE DANS PERSONNAGE OU JOUEUR*/
    default:
        cout << "cas inconnu" << endl;
        return 0;
    }
}

char Moine::initialePerso() const
{
    return 'm';
}