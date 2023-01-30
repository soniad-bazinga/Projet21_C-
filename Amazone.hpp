#ifndef AMAZONE_HPP
#define AMAZONE_HPP

#include "Personnage.hpp"

class Amazone : public Personnage
{
public:
    Amazone();
    int attaquer(int choix, int armePoison) const;
    char initialePerso() const;
};

#endif