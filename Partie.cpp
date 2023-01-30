#include "Partie.hpp"

/*LE CHATEAU: entité statique dans le nombre de pièces, le joueur a accès à 
seulement certains pièces d'après son  niveau actuel, et débloque de nouvelles
pièces en gagnant les combats contre les personnages d'une pièce. 
càd:
On imagine qu'on est dans une pièce A, qui a au plus 2 portes, une porte mène à la pièce 
C et l'autre pièce mène à la porte B. Les deux sont fermés. 
Pour accéder à la porte B, il faut une clé. La clé se trouve parmis les objets de 
la pièce C. Et pour ouvrir la porte C, il faut battre chacun (ou au moins un nombre qu'on 
fixera après) des personnages présents dans la pièce A. Son niveau dépend donc 
du nombre de combats gagnés. 
Ensuite, pour accéder aux objets de la porte C, il faut battre les personnages qui se trouvent 
dans cette pièce et ramasser la clé de la porte B.
La pièce C n'a qu'une porte, celle qui la relie à la pièce A donc pour avancer dans le chateau et 
dans le jeu, il faut passer par la pièce B et donc s'engager dans les combats.

*/

Partie::Partie(int c)
{
    int type = choisirType();
    string prenom = choisirNom(type);
    joueur = new Joueur(prenom, type);
    //cout << "AFFAICHA " << joueur->getPersonnage()->initialePerso() << endl;
    creerChateau(c); /* v"rifier que c est au moins 1 */
    ligne = 0;
    colonne = 0;
};

//TODO : il faut que toutes les pièces soient accessibles depuis la pièce initiale
void Partie::creerChateau(int c)
{
    srand(time(NULL));

    bool n = false;
    bool e = false;
    bool s = false;
    bool o = false;
    vector<vector<Piece *>> v;
    //il y a des contraintes particulieres sur la premiere et derniere ligne
    //ainsi que sur la premiere et derniere colonne
    for (int i = 0; i < c; i++)
    {
        vector<Piece *> vLigne;
        for (int j = 0; j < c; j++)
        {
            do
            {
                //rcout << "boucle infinie ?? i: " << i << " j: " << j << endl;
                if (i != c - 1)
                    s = rand() % 2;
                if (i != 0)
                    n = v[i - 1][j]->getSud();
                if (j != c - 1)
                    e = rand() % 2;
                if (j != 0)
                    o = vLigne[j - 1]->getEst();
                if (i == c - 1 && j == c - 1 && !n && !e && !s && !o)
                {
                    o = true;
                    vLigne[i - 1]->setEst();
                }
            } while (n == false && e == false && s == false && o == false);
            vLigne.push_back(new Piece(n, e, s, o));
            n = false, e = false, s = false, o = false;
        }
        v.push_back(vLigne);
    }
    chateau = v;
};

//On choisit pour l'instant + d'objets que d'adversaires
void Partie::remplirChateau()
{
    srand(time(NULL));
    int n = chateau.size();
    int r;
    vector<vector<int>> piecesAnalysees;
    for (int i = 0; i < n; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < n; j++)
        {
            tmp.push_back(0);
            r = rand() % 10;
            if (r < 6)
            {
                int k = rand() % 5;
                chateau.at(i).at(j)->addObj(new Meuble(k));
            }
            else
            {
                switch (r)
                {
                case 6:
                    chateau.at(i).at(j)->addPerso(new Sorciere());
                    break;
                case 7:
                    chateau.at(i).at(j)->addPerso(new Amazone());
                    break;
                case 8:
                    chateau.at(i).at(j)->addPerso(new Moine());
                    break;
                case 9:
                    chateau.at(i).at(j)->addPerso(new Guerrier());
                    break;
                }
            }
        }
        chateau.at(0).at(0)->addObj(new Meuble(0)); //on doit tjr avoir au moins une arme
        chateau.at(0).at(0)->addObj(new Meuble(4)); //on doit tjr avoir au moins une clef
        piecesAnalysees.push_back(tmp);
    }
    //le but est de s'assurer, dans le cadre d'un chateau avec des pièces non-connexes
    //qu'au moins une clef de teleportation est disponible dans chacune des parties connexes
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!clefDansConnexe(i, j, piecesAnalysees))
                chateau.at(i).at(j)->addObj(new Meuble(4));
            for (int l = 0; l < n; l++)
            {
                for (int m = 0; m < n; m++)
                    piecesAnalysees[l][m] = 0;
            }
        }
    }
};

bool Partie::clefDansConnexe(int i, int j, vector<vector<int>> piecesAnalysees)
{
    int n = chateau.size();
    if (chateau[i][j]->contientClef())
        return true;
    piecesAnalysees[i][j] = 1;
    if ((i + 1) >= 0 && (i + 1) < n && chateau[i][j]->estConnectee(chateau[i + 1][j]) && piecesAnalysees[i + 1][j] == 0 && clefDansConnexe(i + 1, j, piecesAnalysees))
        return true;
    if ((j + 1) >= 0 && (j + 1) < n && chateau[i][j]->estConnectee(chateau[i][j + 1]) && piecesAnalysees[i][j + 1] == 0 && clefDansConnexe(i, j + 1, piecesAnalysees))
        return true;
    if ((i - 1) >= 0 && (i - 1) < n && chateau[i][j]->estConnectee(chateau[i - 1][j]) && piecesAnalysees[i - 1][j] == 0 && clefDansConnexe(i - 1, j, piecesAnalysees))
        return true;
    if ((j - 1) >= 0 && (j - 1) < n && chateau[i][j]->estConnectee(chateau[i][j - 1]) && piecesAnalysees[i][j - 1] == 0 && clefDansConnexe(i, j - 1, piecesAnalysees))
        return true;
    return false;
};

int Partie::choisirType()
{
    int niv;
    do
    {
        cout << "\nTapez un nombre d'id entre 0 et 3, en fonction du type de personnage désiré.\n\n"
             << "+------------------------------------+\n"
             << "| id | type_perso | sante | habilete |\n"
             << "+--------+------------+-------+------+\n"
             << "| 0  | Sorcière   |  200  |   150     |\n"
             << "| 1  | Amazone    |  210  |   200     |\n"
             << "| 2  | Moine      |  250  |   100     |\n"
             << "| 3  | Guerrier   |  200  |   210     |\n"
             << "+------------------------------------+\n\nId : ";
        cin >> niv;
    } while (niv < 0 || niv > 3);
    cout << "Vous incarnez un";
    switch (niv)
    {
    case 0:
        cout << "e sorcière.\n";
        break;
    case 1:
        cout << "e amazone.\n";
        break;
    case 2:
        cout << " moine.\n";
        break;
    case 3:
        cout << " guerrier.\n";
        break;
    }
    cout << endl;
    return niv;
};

string Partie::choisirNom(const int type)
{
    string prenom;
    cout << "Comment s'appellera votre ";
    switch (type)
    {
    case 0:
        cout << "sorcière ?\n";
        break;
    case 1:
        cout << "amazone ?\n";
        break;
    case 2:
        cout << "moine ?\n";
        break;
    case 3:
        cout << "guerrier ?\n";
        break;
    }
    //TODO : gérer les caractères spéciaux
    cin >> prenom;
    cout << endl;
    return prenom;
}

void Partie::deplacement(bool alea)
{
    srand(time(NULL));
    vector<char> portes;
    char res;
    //cout << this;
    do
    {
        cout << "Où voulez vous vous déplacer ?\n"
             << "r : rester dans la même pièce\n";
        if (chateau[ligne][colonne]->getNord())
        {
            cout << "n : aller dans la pièce nord\n";
            portes.push_back('n');
        }
        if (chateau[ligne][colonne]->getEst())
        {
            cout << "e : aller dans la pièce est\n";
            portes.push_back('e');
        }
        if (chateau[ligne][colonne]->getSud())
        {
            cout << "s : aller dans la pièce sud\n";
            portes.push_back('s');
        }
        if (chateau[ligne][colonne]->getOuest())
        {
            cout << "o : aller dans la pièce ouest\n";
            portes.push_back('o');
        }
        if (joueur->clefDansSac())
        {
            cout << "c : utiliser la clef de téléportation\n";
            portes.push_back('c');
        }
        if (alea)
            res = portes[rand() % portes.size()];
        else
            cin >> res;
    } while (res != 'r' && !(find(portes.begin(), portes.end(), res) != portes.end()));
    switch (res)
    {
    case 'n':
        ligne--;
        break;
    case 'e':
        colonne++;
        break;
    case 's':
        ligne++;
        break;
    case 'o':
        colonne--;
        break;
    case 'c':
        teleportation();
        break;
    }
};

void Partie::teleportation()
{
    int i, j;
    do
    {
        cout << "Sur quelle ligne voulez-vous vous téléporter ?\n";
        cin >> i;
    } while (i > chateau.size() || i < 0);
    do
    {
        cout << "Sur quelle colonne voulez-vous vous téléporter ?\n";
        cin >> j;
    } while (j > chateau.size() || j < 0);
    joueur->supprimerClef();
    ligne = i;
    colonne = j;
}

void Partie::deplacementAleatoire()
{
    srand(time(NULL));
    /*le programme doit déplacer tout les autres personnages de manière aléatoire*/
    for (int i = 0; i < chateau.size(); i++)
    {
        for (int j = 0; j < chateau.size(); j++)
        {
            for (int k = 0; k < chateau[i][j]->getRoommates().size(); k++)
            {
                vector<char> portes;
                if (chateau[i][j]->getNord())
                    portes.push_back('n');
                if (chateau[i][j]->getEst())
                    portes.push_back('e');
                if (chateau[i][j]->getSud())
                    portes.push_back('s');
                if (chateau[i][j]->getOuest())
                    portes.push_back('o');
                char r = portes[rand() % portes.size()];
                switch (r)
                {
                case 'n':
                    chateau[i - 1][j]->addPerso(chateau[i][j]->getRoommates()[k]);
                    break;
                case 'e':
                    chateau[i][j + 1]->addPerso(chateau[i][j]->getRoommates()[k]);
                    break;
                case 's':
                    chateau[i + 1][j]->addPerso(chateau[i][j]->getRoommates()[k]);
                    break;
                case 'o':
                    chateau[i][j - 1]->addPerso(chateau[i][j]->getRoommates()[k]);
                    break;
                }
                chateau[i][j]->erase(k);
            }
            /*choisir des coordonnées au hasard et y mettre ces personnages là, 
                penser à les retirer de la pièce(i, j)
                Meuble *meu = v.at(k);
                int x = rand() % chateau.size();
                int y = rand() % chateau.size();
                auto elem_to_erase = v.begin() + k;
                if (elem_to_erase != v.end())
                    v.erase(elem_to_erase);
                /*on le place mnt dans la pièce choisie aléatoirement*/
            //chateau.at(x).at(i)->addObj(meu);*/
        }
    }
}

int Partie::tjrVivant(Personnage *ennemi)
{ /*afin de déterminer si l'un 
des combattant est mort ce qui impliquerai la fin du combat en cours*/
    if (joueur->getPersonnage()->getSante() <= 0)
    {
        cout << "OH NO! U DIED :(." << endl;
        return 2;
    }
    if (ennemi->getSante() <= 0)
    {
        cout << "ENNEMI VAINCU." << endl;
        return 1;
    }
    return 0;
}

void Partie::choisirAction(Personnage *ennemi, Meuble *boissonInterdite)
{
    char rep;
    /*c'est au joueur d'attaquer*/
    cout << "À toi de jouer! " << endl;
    /*affichage du contenu du sac pour donner choix au joueur*/
    //cout << joueur->getSac(); /*PROBLEME D'AFFICHAGE ICI*/
    cout << "Choisis ce que tu veux faire: " << endl;
    joueur->afficheSacoche();
    /*réponse de 0 à taille du sac*/
    /*remplir son sac ? */
    cout << "u: Utiliser ton sac" << endl;
    cout << "r: remplir son sac" << endl;
    cin >> rep;
    int x = -1;
    switch (rep)
    {
    case 'u':
        if (joueur->getSac().size() == 0)
        {
            cout << "ton sac est vide, remplis d'abord." << endl;
        }
        else
        {
            joueur->afficheSacoche();
            cout << "Choisi ton outil: (L'initiale suffira, merci.) ";
            cin >> rep;
            try
            {
                if (joueur->chercherObjet(rep))
                {
                    int degats = 0;
                    if (rep != 'c')
                        degats = joueur->whatDoUDo(boissonInterdite, rep);
                    else
                    {
                        teleportation();
                        joueur->supprime(rep);
                        return;
                    }
                    if (rep != 'b' && rep != 'a')
                        joueur->supprime(rep);

                    /*CAS OÙ LE JOUEUR CHOISIT MEDICAMENT OU BOUCLIER*/
                    if (degats >= 0)
                    {
                        joueur->getPersonnage()->setSante(degats);
                        cout << "SANTE: " << joueur->getPersonnage()->getSante();
                    }
                    /*CAS DANS UNE ATTAQUE */
                    else
                    {
                        ennemi->setSante(degats);
                        cout << "SANTE ENNEMI " << ennemi->getSante() << endl;
                    }
                }
                else
                {
                    throw x;
                }
            }
            catch (int x)
            {
                cout << "mauvaise saisie." << endl;
            }
        }
        break;
    case 'r':
        cout << "Que voulez-vous prendre? Entrer l'initiale de l'objet se trouvant dans la pièce." << endl;
        cin >> rep;
        Meuble *newOne = getPieceCourante()->chercherObjet(rep);
        try
        {
            if (newOne != nullptr)
            {
                joueur->remplirSac(newOne);
                getPieceCourante()->supprime(newOne);
                /*supprimer l'objet du vecteur decoration de la piece*/
            }
            else
            {
                throw x;
            }
        }
        catch (int x)
        {
            cout << "Il y'a eu une erreur de saisie." << endl;
        }
        joueur->afficheSacoche();
    }
    /*TO DO : rajouter une option pour abandonner le combat? Or not ? it's ride or die*/

    /*on a trouvé une arme! On fait quoi mnt? */
    /*une arme devrait avoir une valeur qui correspond au dégat qu'elle 
                  inflige lors d'une attaque*/

    /*IDEE: le poison peut s'utiliser sur une arme pour faire plus de dégats, 
                  on demande au joueur s'il veut empoisonner la lame de son arme (si dans son 
                  sac, il y'a bien du poison) les dégats s'addionnent et c'est un carnage */

    /*DONC on cherche du poison dans le sac, et on demande au joueur s'il veut utiliser 
                  son attaque ultime! */
    /*si l'on ne trouve pas d'armes, le joueur peut utiliser du poison ?*/
};

void Partie::subirAction(Personnage *ennemi)
{
    srand(time(NULL));
    int rep;
    /*c'est à l'ennemi d'attaquer*/
    /*il faudra laisser le hasard*/
    cout << "Attaque de l'ennemi" << endl;
    int taVieEnJeu = rand() % 4;
    if (taVieEnJeu == 3 || taVieEnJeu == 1)
    {
        if (ennemi->getSante() >= 10)
        {
            taVieEnJeu = 0;
        }
    }
    int res = ennemi->attaquer(taVieEnJeu, taVieEnJeu % 2);
    if (res < 0)
        joueur->getPersonnage()->setSante(res);
    else
        ennemi->setSante(res);
    cout << "Votre santé: " << joueur->getPersonnage()->getSante() << endl;
}

Piece *Partie::getPieceCourante() const
{
    return chateau.at(ligne).at(colonne);
}

/*void Partie::descriptionPiece ()
{
    /*doit renvoyer la liste des objets et des personnages présents dans la pièce.*/
// pour le moment,on va simplment appeler les getters de la classe Piece

//}

/*prend en entrée la pièce courante */
/*à la fin du combat, il faudra mettre à jour le contenu du sac 
Si le combat a été gagné par le joueur, on diminue les poisons et 
médicaments si utilisés,
si le combat a été perdu, on diminue ÉGALEMENT LES ARMES ET BOUCLIERS
s'ils ont été utilisés lors du combat, 
désolé mon pote mais on se fait dépouillé quand un perd une bataille*/

void Partie::combat(Piece *pieceCourante)
{ /*le joueur doit s'engager en combat avec chacun des personnages présents*/
    /*déroulement d'un combat: 
        - parcourir la liste des personnages prése,ts dans la pièce
        - s'engager en combat avec chacun d'eux 
        - le résultat du combat prend en compte: 
            * l'habileté des personnages 
            * des armes et des boucliers 
            * du type des personnages 
            * du hasard ?? 
    */

    /*vérifier si le joueur possède du poison dans son sac, utile pour 
    la fonction WhatDoUDo de Meuble après*/
    Meuble *boissonInterdite = joueur->isTherePoison();
    int pourcentage1, pourcentage2;
    srand(time(NULL));
    if (pieceCourante->getRoommates().size() == 0)
    {
        cout << "Pas d'ennemis en vue, c'est tranquille ici.." << endl;
        choisirAction(nullptr, boissonInterdite);
    }
    else
    {
        vector<Personnage *>::iterator it;
        for (Personnage *ennemi : pieceCourante->getRoommates())
        {
            cout << endl
                 << "NOUVEAU COMBAT" << endl;
            ennemi->setSante(-60); /*sinon le jeu est trop difficile*/

            /*let the combat begin*/
            /*idée:
       - calculer un poucentage pour chaque personnage à partir des
       paramètres cités en haut puis comparer les résultats finaux pour 
       décider du résultat du combat  
       --> à la fin du combat il faudra améliorer (ou baisser?) l'abilité du joueur
       /*idée abandonnée*/
            /*armes et boucliers*/
            /*utilsier le hasard pour déterminer qui attaque en premier, en vérifiant que
      le personnage possède bien une arme*/
            /*FAIRE UNE BOUCLE: TANT QU'AUCUN DES DEUX N'EST MORT, LE COMBAT CONTINUE*/
            while (tjrVivant(ennemi) == 0)
            {
                cout << "SANTE: " << joueur->getPersonnage()->getSante() << endl;
                cout << "SANTE ENNEMI: " << ennemi->getSante() << endl;
                int ligne_init = ligne;
                int colonne_init = colonne;
                choisirAction(ennemi, boissonInterdite);
                if (ligne_init != ligne || colonne_init != colonne)
                    return;
                if (ennemi->getSante() <= 0)
                {
                    /*on le supprime de la liste des personnages*/
                    //delete pieceCourante->getRoommates().at(idc);
                    //pieceCourante->getRoommates().erase(pieceCourante->getRoommates().begin() + idc);

                    break;
                }
                subirAction(ennemi);
            }

            /*décider de l'issue du combat et mise à jour des capacités du joueur*/
            /*si le joueur esr tjr vivant, le combat a été gagné et la partie continue*/
            if (tjrVivant(ennemi) != 2)
            {
                /*on glow up */
                joueur->getPersonnage()->amelioreHabilete(ennemi->getHabilete() / 2);
                joueur->getPersonnage()->setSante(200);
            }
            else
            {
                finPartie(1);
            }
        }
        /*on supprime les perso morts*/
        /*for (it = pieceCourante->getRoommates().begin(); it != pieceCourante->getRoommates().end();)
        {
            if ((*it)->getSante() <= 0)
            {
                delete *it;
                it = pieceCourante->getRoommates().erase(it);
            }
            else
            {
                ++it;
            }
        }*/
    }
    /*les combats sont finits, si le joueur est toujours vivant, il peut 
    poursuivre vers la pièce suivante.*/
};

bool Partie::finPartie(int signal)
{
    if (signal == 1)
    {
        cout << "PARTIE TERMINEE. MERCI D'AVOIR JOUÉ, À LA PROCHAINE!" << endl;
        exit(0);
    }
    return 0;
};

void Partie::gerePartie()
{
    if (tjrVivant(joueur->getPersonnage()) != 2)
    {
        remplirChateau();
    }
    else
    {
        finPartie(1);
        exit(0);
    }
    while (!finPartie(0))
    {
        cout << this;
        deplacement(false);
        deplacementAleatoire();
        cout << "**DÉPLACEMENTS**" << endl;
        cout << this;
        /*le joueur est présenté avec une description de la pièce: personnages et objets présents.*/
        combat(getPieceCourante());
    }
};

/*//ADD TO SAVE
void Partie::save(){
    string json = string("{\"ligne\":")+to_string(ligne)+string(",\"colonne\":")+to_string(colonne)+string(",");
    json = json + joueur->save();
    json = json + "\"chateau\":[";
    for(int i=0; i<chateau.size(); i++){
        json = json + string("[");
        for(int j=0; j<chateau.size();j++){
            json = json + chateau[i][j]->save();
            if (j!=chateau.size()-1) json = json + string(",");
        }
        json = json + string("]");
        if (i!=chateau.size()-1) json = json + string(",");
    }
    json = json + "]";
    json = json + "}";

    ofstream fic("save.json");

    if(fic){
        fic << json;
    }else{
        //TODO : ajouter erreur
        cout << "error" << endl;
    }
};

Partie* Partie::useSave(const char* file){
    FILE* fp = fopen("save.json", "r"); 
 
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
 
    Document document;
    document.ParseStream(is);
 
    fclose(fp);

    ligne = document["ligne"].GetInt();
    colonne = document["colonne"].GetInt();
    joueur = new Personnage(document["nom"].GetString(), document["personnage"].GetInt());
    joueur->useSave(document["habilete"].GetInt(), document["sante"].GetInt());

    const Value& c = document["chateau"];
    assert(c.IsArray());
    for (int i=0; i<c.Size(); i++){
        vector<Piece*> l;
        for (int j=0; j<c[i].Size(); j++){
            l.push_back(new Piece(c[i].GetArray()[j][0].GetInt(),c[i].GetArray()[j][1].GetInt(),c[i].GetArray()[j][2].GetInt(),c[i].GetArray()[j][3].GetInt()));
        }
        chateau.push_back(l);
    }
    return nullptr;
};*/

ostream &operator<<(ostream &out, Partie *p)
{
    vector<vector<Piece *>> c = p->getChateau();
    int n = c.size();
    out << "Voici l'état actuel du château : \n";
    //premiere ligne :
    out << "+";
    for (int i = 0; i < n; i++)
        out << "------+";
    out << endl;

    //pieces :
    for (int i = 0; i < n; i++)
    {
        //premiere ligne de chaque piece :
        for (int j = 0; j < n; j++)
        {
            out << "|";
            if (c[i][j]->contientClef())
                out << "c";
            else
                out << " ";
            if (c[i][j]->contientArme())
                out << "a";
            else
                out << " ";
            if (c[i][j]->contientBouclier())
                out << "b";
            else
                out << " ";
            if (c[i][j]->contientPoison())
                out << "p";
            else
                out << " ";
            if (c[i][j]->contientMedicament())
                out << "m";
            else
                out << " ";
            out << " ";
        }
        out << "|" << endl;
        //ligne avec les portes est et ouest :
        for (int j = 0; j < n; j++)
        {
            if (c[i][j]->getOuest())
                out << " ";
            else
                out << "|";
            if (p->getLigne() == i && p->getColonne() == j)
            {
                out << " " << p->getJoueur()->getNom().substr(0, 4) << " ";
                for (int l = 0; l < 4 - (p->getJoueur()->getNom()).length(); l++)
                    out << " ";
            }
            else
                out << "      ";
        }
        out << "|" << endl;

        for (int j = 0; j < n; j++)
        {
            out << "| ";
            string perso = c[i][j]->listePerso();
            out << perso;
            for (int l = 0; l < 4 - perso.length(); l++)
                out << " ";
            out << " ";
        }
        out << "|" << endl
            << "+";
        for (int j = 0; j < n; j++)
        {
            out << "--";
            if (c[i][j]->getSud())
                out << "  ";
            else
                out << "--";
            out << "--+";
        }
        out << endl;
    }
    out << endl
        << endl;

    return out;
};
