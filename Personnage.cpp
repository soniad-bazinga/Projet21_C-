#include "Personnage.hpp"
#include "Meuble.hpp"

Personnage::Personnage(int san, int hab) : sante(san), habilete(hab) {}

void Personnage::setSante(const int val)
{
    sante += val;
}

void Personnage::setHabilete(const int val)
{
    habilete = val;
}

ostream &operator<<(ostream &out, Personnage *p)
{
    out << " : sante " << p->getSante() << " | habilete " << p->getHabilete() << endl;
    return out;
};

void Personnage::inflifeEffet(int degat, int *sante)
{
    *sante += degat;
}

int Personnage::attaquer(int choix, int poison) const
{
    return 0;
}

void Personnage::amelioreHabilete(const int val)
{
    habilete += val;
}

char Personnage::initialePerso() const
{
    return 'z';
}

/*//ADD TO SAVE + SAC
string Personnage::save(){
    string json = string("\"nom\":\"")+nom+"\",\"sante\":"+to_string(sante)+",\"habilete\":"+to_string(habilete)+",\"personnage\":"+to_string(personnage)+string(",");
    return json;
};

Personnage* Personnage::useSave(int h, int s){
    this->sante = s;
    this->habilete = h;
    return this;
};

/*
template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}
*/