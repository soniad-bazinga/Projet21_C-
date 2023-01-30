#ifndef GUERRIER_HPP
#define GUERRIER_HPP

#include "Personnage.hpp"

class Guerrier :public Personnage
{
private:
public:
   Guerrier(); 
   int attaquer(int choix,  int armePoison) const;  
    char initialePerso() const;
};

#endif