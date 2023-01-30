#include "Meuble.hpp"

Meuble::Meuble(int number)
{
    if (number <= 4)
        obj = Objet(number);
    else //TODO : erreur
        cout << "L'objet que vous tentez de créer n'existe pas." << endl;
}

Meuble::Objet Meuble::getObj() const
{
    return obj;
}

bool Meuble::estClef()
{
    return (obj == Objet::Cle);
}

bool Meuble::estArme()
{
    return (obj == Objet::Arme);
}

bool Meuble::estBouclier()
{
    return (obj == Objet::Bouclier);
}

bool Meuble::estPoison()
{
    return (obj == Objet::Poison);
}

bool Meuble::estMedicament()
{
    return (obj == Objet::Medicament);
}

ostream &operator<<(ostream &out, const Meuble *meu)
{
    switch (meu->getObj())
    {
    case 0:
        out << "Arme";
        break;
    case 1:
        out << "Bouclier";
        break;
    case 2:
        out << "Poison";
        break;
    case 3:
        out << "Medicament";
        break;
    case 4:
        out << "Cle";
        break;
    }
    return out;
}