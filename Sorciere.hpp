#ifndef SORCIERE_HPP
#define SORCIERE_HPP

#include "Personnage.hpp"

class Sorciere : public Personnage
{
private:
public:
    Sorciere();
    int attaquer(int choix, int armePoison) const;
    char initialePerso() const;
};

#endif