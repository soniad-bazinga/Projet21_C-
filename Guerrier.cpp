#include "Guerrier.hpp"

Guerrier::Guerrier()
{
    this->setSante(200);
    this->setHabilete(210);
}

int Guerrier::attaquer(int choix, int armePoison) const
{
    switch (choix)
    {
    case 0: /*Arme*/
        if (armePoison != 0)
        {
            /*l'arme est empoisonnée*/
            cout << "ARME EMPOISONNE UTILISEE" << endl;
            return -100;
        }
        else
        {
            cout << "ARME UTILISEE" << endl;
            return -70;
        }
    case 1: /*Bouclier*/
        cout << "BOUCLIER UTILISE" << endl;
        return 55;
    case 2: /*Poison*/
        cout << "POISON UTILISE" << endl;
        return -30;
    case 3: /*Medicament*/
        cout << "MEDICAMENT UTILISE" << endl;
        return 40;
    /*AJOUTER LE CAS POUR LA CLÉ MAIS DOIT PLUTOT ETRE MISE DANS PERSONNAGE OU JOUEUR*/
    default:
        cout << "cas inconnu" << endl;
        return 0;
    }
}

char Guerrier::initialePerso() const
{
    return 'g';
}