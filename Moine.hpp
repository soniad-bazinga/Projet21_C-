#ifndef MOINE_HPP
#define MOINE_HPP

#include "Personnage.hpp"

class Moine : public Personnage
{
private:
public:
    Moine();
    int attaquer(int choix, int armePoison) const;
    char initialePerso() const;

};

#endif