#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include "Personnage.hpp"
#include "Objet.hpp"
#include <string>

using namespace std;

class Piece
{
private:
    bool nord;
    bool est;
    bool sud;
    bool ouest;
    //vector<Meuble*> contenu;
    vector<Personnage *> roommates; /*contient la liste des personnages présents dans la pièce*/
    vector<Meuble *> decoration;    /*contient la liste des objets présents dans la pièce*/
public:
    Piece(bool n, bool e, bool s, bool o) : nord{n}, est{e}, sud{s}, ouest{o} {};
    bool estConnectee(Piece *p);
    bool getNord() const { return nord; };
    bool getEst() const { return est; };
    bool getSud() const { return sud; };
    bool getOuest() const { return ouest; };
    void setEst() { est = true; };
    vector<Personnage *> getRoommates() const { return roommates; };
    vector<Meuble *> getDecoration() const { return decoration; }
    void addPerso(Personnage *p);
    void addObj(Meuble *o);
    bool contientClef();
    bool contientArme();
    bool contientBouclier();
    bool contientPoison();
    bool contientMedicament();
    Meuble *chercherObjet(char initiale);
    string listePerso();
    void erase(int k);
    void supprime (Meuble* o);
    //ADD TO SAVE
    string save();
};

#endif