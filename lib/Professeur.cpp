#include <iostream>
#include <cstring>
#include "Professeur.h"
#include "planifiable.h"
using namespace std;

Professeur::Professeur() : Professeur(0,"default","default"){}
Professeur::Professeur(const int i,const char* name,const char* S_name): Planifiable(0),nom(NULL),prenom(NULL)
{setNom(name);setPrenom(S_name);setId(i);}

Professeur::Professeur(const Professeur &P):Professeur(P.id,P.nom,P.prenom){}
Professeur::~Professeur(){if(nom) delete nom; if(prenom) delete prenom;}

void Professeur::setNom(const char *Name)
{
    if(strlen(Name) == 0) { cerr << "pas de nom encode." << endl; return;}
    if(nom) delete nom;

    nom = new char[strlen(Name)+1];
    strcpy(nom,Name);
}
void Professeur::setPrenom(const char *S_Name)
{
    if(strlen(S_Name) == 0) { cerr << "pas de nom encode." << endl; return;}
    if(prenom) delete prenom;

    prenom = new char[strlen(S_Name)+1];
    strcpy(prenom,S_Name);
}

const char* Professeur::getNom() const{return nom;}
const char* Professeur::getPrenom() const{return prenom;}

Professeur& Professeur::operator=(const Professeur &P)
{strcpy(nom,P.nom);strcpy(prenom,P.prenom);id = P.id;return *this;}

ostream& operator<<(ostream& os,const Professeur &P)
//{os << P.id << ';' << P.nom << ';' << P.prenom; return os;}
{os << P.nom << ';' << P.prenom << ';' << std::endl;; return os;}




const char* Professeur::Txt()
{
    char tmp[100];
    sprintf(tmp,"%s %s",nom,prenom);
    if(txt) delete txt;
    txt = new char[strlen(tmp)+1];
    strcpy(txt,tmp);
    return txt;
}
const char* Professeur::Tuple()
{
    char tmp[100];
    sprintf(tmp,"%d;%s;%s",id,nom,prenom);
    if(txt) delete txt;
    txt = new char[strlen(tmp)+1];
    strcpy(txt,tmp);
    return txt;
}


int Professeur::compare(const Professeur &prof)
{
    if(strcmp(nom,prof.nom) > 0) return 1;
    if(strcmp(nom,prof.nom) < 0) return -1;

    if(strcmp(prenom,prof.prenom) > 0) return 1;
    if(strcmp(prenom,prof.prenom) < 0) return -1;


    return 0;
}

int Professeur::operator==(const Professeur &prof) { return compare(prof) == 0;}
int Professeur::operator>(const Professeur &prof) { return compare(prof) == 1;}
int Professeur::operator<(const Professeur &prof) { return compare(prof) == -1;}


void Professeur::Save(ofstream &fichier) const
{
    int sizeNom = strlen(nom);
    int sizePrenom = strlen(prenom);
    fichier.write((char*)&id,sizeof(int));

    fichier.write((char*)&sizeNom,sizeof(int));
    fichier.write(nom,sizeNom);

    fichier.write((char*)&sizePrenom,sizeof(int));
    fichier.write(prenom,sizePrenom);
}
void Professeur::Load(ifstream &fichier)
{
    int sizeNom;
    int sizePrenom;
    fichier.read((char*)&id,sizeof(int));

    fichier.read((char*)&sizeNom,sizeof(int));

    if(nom) delete nom;

    nom = new char[sizeNom + 1];
    fichier.read(nom,sizeNom);
    nom[sizeNom] = '\0';

    fichier.read((char*)&sizePrenom,sizeof(int));

    if(prenom) delete prenom;
    
    prenom = new char[sizePrenom + 1];
    fichier.read(prenom,sizePrenom);
    prenom[sizePrenom] = '\0';


    std::cout << "Professeur::Lecture nom=" << nom << std::endl;
    std::cout << "Professeur::Lecture prenom=" << prenom << std::endl;
}