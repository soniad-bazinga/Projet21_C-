#ifndef MEUBLE_HPP
#define MEUBLE_HPP

#include <iostream>
using namespace std;

class Meuble
{ /*changer le nom de la classe par pitié, on dirait 
qu'on vend des canapés*/
private:
    enum Objet
    {
        Arme,
        Bouclier,
        Poison,
        Medicament,
        Cle
    };

    Objet obj;
    friend class Joueur; 
    friend class Piece; 
    //friend class Personnage; /*pour avoir acces aux types d'Objet*/
public:
    Meuble(int);
    Objet getObj() const;
    bool estClef();
    bool estArme();
    bool estBouclier();
    bool estPoison();
    bool estMedicament();
};

ostream &operator<<(ostream &out, const Meuble *);

#endif