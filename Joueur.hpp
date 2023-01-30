#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <vector>
#include <ostream>
#include "Personnage.hpp"
#include "Moine.hpp"
#include "Guerrier.hpp"
#include "Sorciere.hpp"
#include "Amazone.hpp"

using namespace std;

/*class Personnage
{
};*/

class Joueur
{
private:
    const string nom;
    Personnage *perso = nullptr;
    vector<Meuble *> sac;

public:
    Joueur(string nom, int personnage);
    Personnage *getPersonnage() const;
    string getNom() const;
    vector<Meuble *> getSac() const;
    void remplirSac(Meuble *obj); /*couldn't use const here*/
    int chercherSac(Meuble *obj);
    Meuble *chercherObjet(char initiale);
    Meuble *isTherePoison() const;
    int whatDoUDo(Meuble *, char choix);
    void afficheSacoche() const;
    bool clefDansSac() const;
    void supprimerClef();
    void supprime(char c);
};

template <typename T>
ostream &operator<<(ostream &out, const vector<T *> &sac);

#endif