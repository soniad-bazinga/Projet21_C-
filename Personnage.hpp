#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <string>
#include <ostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>
#include "Meuble.hpp"

using namespace std;

class Personnage
{
private:
    int sante;
    int habilete;

public:
    Personnage() { cout << "Creation des personnages.." << endl; }; /*par défaut*/
    Personnage(int, int);
    int getSante() { return sante; };
    void setSante(const int);
    int getHabilete() { return habilete; };
    void setHabilete(const int);
    void amelioreHabilete(const int);
    void inflifeEffet(int degat, int *sante);
    virtual int attaquer(int, int) const;
    virtual char initialePerso() const;
    /*//ADD TO SAVE
    string save();
    Personnage* useSave(int h, int s);*/
};

ostream &operator<<(ostream &out, Personnage *p);
#endif
