#include <iostream>
#include "Groupe.h"
#include <cstring>
#include "planifiable.h"
using namespace std;



Groupe::Groupe():Groupe(0,0){}
Groupe::Groupe(const int j,const int i):Planifiable(0), numero(0) {numero = i;setId(j);}
Groupe::Groupe(const Groupe &G): Groupe(G.id,G.numero){}
Groupe::~Groupe(){}


void Groupe::setNumero(const int i){numero = i;}
int Groupe::getNumero() const {return numero;}

//ostream& operator<<(ostream& os,const Groupe& G){os << G.id << ';' << G.numero;return os;}

Groupe& Groupe::operator=(const Groupe &G){id = G.id;numero = G.numero;return *this;}


const char* Groupe::Txt()
{
    char tmp[100];
    sprintf(tmp,"G%d",numero);
    if(txt) delete txt;
    txt = new char[strlen(tmp)+1];
    strcpy(txt,tmp);
    return txt;
}
const char* Groupe::Tuple()
{
    char tmp[100];
    sprintf(tmp,"%d;%d",id,numero);
    if(txt) delete txt;
    txt = new char[strlen(tmp)+1];
    strcpy(txt,tmp);
    return txt;
}

int Groupe::compare(const Groupe &grp)
{
    if(numero > grp.numero) return 1;
    if(numero < grp.numero) return -1;


    return 0;
}

int Groupe::operator==(const Groupe &grp) { return compare(grp) == 0;}
int Groupe::operator>(const Groupe &grp) { return compare(grp) == 1;}
int Groupe::operator<(const Groupe &grp) { return compare(grp) == -1;}

void Groupe::Save(ofstream &fichier) const
{
    fichier.write((char*)(&id),sizeof(int));
    fichier.write((char*)(&numero),sizeof(int));
}
void Groupe::Load(ifstream &fichier)
{
    fichier.read((char*)(&id),sizeof(int));
    fichier.read((char*)(&numero),sizeof(int));

    std::cout << "Groupe::Lecture numero=" << numero << std::endl;
}

ostream& operator<<(ostream& os,const Groupe& grp) 
{
    os << grp.getNumero() << ";" << std::endl;
    return os;
}