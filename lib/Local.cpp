#include <iostream>
#include <cstring>
#include "Local.h"
#include "planifiable.h"
using namespace std;



Local::Local():Local(0,"default"){}
Local::Local(const int i,const char *Name):nom(NULL){setNom(Name);setId(i);}
Local::Local(const Local &L):Local(L.getId(),L.getNom()){}
Local::~Local(){}

void Local::setNom(const char *Name)
{
    if(strlen(Name) == 0){ cerr << "aucune entree." << endl;return;}
    if(nom) delete nom;
    nom = new char[strlen(Name)+1];
    strcpy(nom,Name);
}
const char* Local::getNom()const {return nom;}

//ostream& operator<<(ostream& os,const Local& L) {os << L.id << ';' << L.nom; return os;}
ostream& operator<<(ostream& os,const Local& L) {os << L.nom << ';' << std::endl; return os;}

Local& Local::operator=(const Local &L){id = L.id;setNom(L.nom);return *this;}


const char* Local::Txt()
{
    char tmp[100];
    sprintf(tmp,"%s",nom);
    if(txt) delete txt;
    txt = new char[strlen(tmp)+1];
    strcpy(txt,tmp);
    return txt;
}
const char* Local::Tuple()
{
    char tmp[100];
    sprintf(tmp,"%d;%s",id,nom);
    if(txt) delete txt;
    txt = new char[strlen(tmp)+1];
    strcpy(txt,tmp);
    return txt;
}

int Local::compare(const Local &loc)
{
    if(strcmp(nom,loc.nom) > 0) return 1;
    if(strcmp(nom,loc.nom) < 0) return -1;

    return 0;
}

int Local::operator==(const Local &loc) { return compare(loc) == 0;}
int Local::operator>(const Local &loc) { return compare(loc) == 1;}
int Local::operator<(const Local &loc) { return compare(loc) == -1;}

void Local::Save(ofstream &fichier) const
{
    int sizeNom = strlen(nom);
    fichier.write((char*)(&id),sizeof(int));
    fichier.write((char*)(&sizeNom),sizeof(int));

    fichier.write(nom,sizeNom);
}
void Local::Load(ifstream &fichier)
{
    int sizeNom;
    fichier.read((char*)(&id),sizeof(int));
    fichier.read((char*)(&sizeNom),sizeof(int));

    if(nom) delete nom;
    
    nom = new char[sizeNom + 1];

    fichier.read(nom,sizeNom);
    nom[sizeNom] = '\0';

    std::cout << "LOCAL::Lecture nom=" << nom << std::endl;

}