#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <ostream>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include "Piece.hpp"
#include "Joueur.hpp"
#include "Meuble.hpp"

using namespace std;

class Partie
{
private:
    vector<vector<Piece *>> chateau;
    int ligne;
    int colonne;
    Joueur *joueur;

public:
    Partie(int c); /*c est le nombre de pièces du chateau*/
    //initialise le vecteur chateau
    //TODO : initialise pas vraiment, modifie plutot ??
    void creerChateau(int c);
    //TODO : permettre au joueur de choisir le niveau et remplir le chateau en fcontion
    void remplirChateau(); //remplit le chateaux d'objets, le remplir ensuite de personnages ?
    vector<vector<Piece *>> getChateau() { return chateau; };
    int getLigne() const { return ligne; };
    int getColonne() const { return colonne; };
    Piece *getPieceCourante() const;
    Joueur *getJoueur() const { return joueur; };
    int choisirType();
    string choisirNom(const int type);
    void deplacement(const bool alea);
    void deplacementAleatoire();
    void descriptionPiece();
    void combat(Piece *);
    void choisirAction(Personnage *, Meuble *);
    void subirAction(Personnage *);
    bool finPartie(int signal);
    void gerePartie();
    int tjrVivant(Personnage *);
    bool clefDansConnexe(int i, int j, vector<vector<int>> piecesAnalysees);
    void teleportation();
    /*//ADD TO SAVE
    void save();
    Partie* useSave(const char* file);*/
};

ostream &operator<<(ostream &out, Partie *p);

#endif