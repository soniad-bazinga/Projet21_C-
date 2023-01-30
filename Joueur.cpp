#include "Joueur.hpp"

Joueur::Joueur(string n, int p) : nom(n)
{
    switch (p)
    {
    case 0:
        perso = new Sorciere();
        break;
    case 1:
        perso = new Amazone();
        break;
    case 2:
        perso = new Moine();
        break;
    case 3:
        perso = new Guerrier();
        break;
    default:
        cout << "erreur de choix de personnage" << endl;
    }
}

Personnage *Joueur::getPersonnage() const
{
    return perso;
}

string Joueur::getNom() const
{
    return nom;
}

void Joueur::afficheSacoche() const
{
    cout << "Contenu de ta sacoche: ";
    if (sac.size() == 0)
    {
        cout << "que de la poussière, remplis ton sac!" << endl;
    }
    for (Meuble *meu : sac)
    {
        cout << meu << "\t";
    }
    cout << endl;
}

vector<Meuble *> Joueur::getSac() const
{
    return sac;
}

template <typename T>
ostream &operator<<(ostream &out, const vector<T *> &sac)
{
    /*pour afficher le contenu du sac*/
    out << "Contenu de votre saccoche: ";
    for (Meuble *meu : sac)
    {
        out << meu << "\t";
    }
    out << endl;
    return out;
}

/*fonction qui vérifie si le sac contient du poison*/
Meuble *Joueur::isTherePoison() const
{
    for (int i = 0; i < sac.size(); i++)
    {
        if (sac.at(i)->getObj() == Meuble::Poison)
        {
            return sac.at(i);
        }
    }
    return nullptr;
}

int Joueur::chercherSac(Meuble *obj)
{
    for (Meuble *meu : sac)
    {
        if (meu->estArme() && obj->estArme() || meu->estClef() && obj->estClef() || meu->estBouclier() && obj->estBouclier() || meu->estPoison() && obj->estPoison() || meu->estMedicament() && obj->estMedicament())
        {
            return 1;
        }
    }
    return 0;
}

Meuble *Joueur::chercherObjet(char initiale)
{
    switch (initiale)
    {
    case 'a':
        /*on cherche une arme*/
        for (Meuble *meu : sac)
        {
            if (meu->obj == Meuble::Objet::Arme)
            {
                return meu;
            }
        }
        break;
    case 'p':
        /*on cherche un poison*/
        for (Meuble *meu : sac)
        {
            if (meu->obj == Meuble::Objet::Poison)
            {
                return meu;
            }
        }
        break;
    case 'm':
        /*on cherche un medoc*/
        for (Meuble *meu : sac)
        {
            if (meu->obj == Meuble::Objet::Medicament)
            {
                return meu;
            }
        }
        break;
    case 'c':
        /*on cherche une clé*/
        for (Meuble *meu : sac)
        {
            if (meu->obj == Meuble::Objet::Cle)
            {
                return meu;
            }
        }
        break;
    case 'b':
        /*on cherche un bouclier*/
        for (Meuble *meu : sac)
        {
            if (meu->obj == Meuble::Objet::Bouclier)
            {
                return meu;
            }
        }
        break;
    }
    return nullptr;
}

void Joueur::remplirSac(Meuble *obj)
{
    if (sac.size() < 4)
    {
        /*vérifier que le sac ne contient pas déja l'objet*/
        if (chercherSac(obj) == 0)
        {
            sac.push_back(obj);
        }
        else
        {
            cout << "Vous avez déja cet objet dans votre sacoche. Ne soyez pas trop gourmand." << endl;
        }
    }
}

int Joueur::whatDoUDo(Meuble *BoissonInterdite, char choix)
{

    Meuble::Objet obj = chercherObjet(choix)->getObj();
    char rep;
    //int choix = -1;
    int poison = 0;
    switch (obj)
    {
    case Meuble::Arme:
        /*dans ce cas là, on peut demander au joueur 
            s'il veut empoisonner sa lame
            mais seulement si dans son sac, il y'a du poison*/
        /*il faut mettre à jour le sac*/
        /*une fois utilisée, le pointeur sur l'objet poison 
        deviendra nullptr*/
        cout << "Utiliser Arme ? O/N" << endl;
        cin >> rep;
        if (rep == 'O')
        {
            choix = 0;
            if (BoissonInterdite != nullptr)
            {
                /*on demande d'abord svp*/
                cout << "Empoisonner arme ? O/N" << endl;
                cin >> rep;
                if (rep == 'O')
                {
                    poison = 1;
                    BoissonInterdite = nullptr;
                }
            }
        }
        break;
        break;
    case Meuble::Bouclier:
        cout << "Utiliser Bouclier? O/N" << endl;
        cin >> rep;
        if (rep == 'O')
            choix = 1;
        break;
    case Meuble::Poison:
        if (BoissonInterdite != nullptr)
        {
            /*poison tjr dispo*/
            cout << "Empoisonner ennemi ? O/N" << endl;
            cin >> rep;
            if (rep == 'O')
                choix = 2;
        }
        else
        {
            return 0;
        }
        break;
    case Meuble::Medicament:
        cout << "Soigner blessures? O/N" << endl;
        cin >> rep;
        if (rep == 'O')
            choix = 3;
        /*RAJOUTER LE CAS DE LA CLÉ !*/
        break;
    default:
        cout << "default case, weird.." << endl;
        return 0;
        break;
    }
    return perso->attaquer(choix, poison);
}

bool Joueur::clefDansSac() const{
    for (int i=0; i<sac.size(); i++){
        if (sac[i]->estClef()) return true;
    }
    return false;
}

void Joueur::supprimerClef(){
    for (int i=0; i<sac.size(); i++){
        if (sac[i]->estClef()){
            sac.erase(sac.begin() + i);
            return;
        }
    }
}

void Joueur::supprime(char c){
    for(int i=0;i<sac.size();i++){
        if(sac[i]->estMedicament() && c=='m'){
            sac.erase(sac.begin() + i);
            return;
        }
        if (sac[i]->estBouclier() && c=='b'){
            sac.erase(sac.begin() + i);
            return;
        }
        if (sac[i]->estClef() && c=='c'){
            sac.erase(sac.begin() + i);
            return;
        }
        if (sac[i]->estPoison() && c=='p'){
            sac.erase(sac.begin() + i);
            return;
        }
        if (sac[i]->estArme() && c=='a'){
            sac.erase(sac.begin() + i);
            return;
        }
    }
}