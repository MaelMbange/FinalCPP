#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Timing.h"
#include "Temps.h"
#include "TimingException.h"
#include <ostream>
#include <fstream>
using namespace std;

const char* Timing::LUNDI = "Lundi";
const char* Timing::MARDI = "Mardi";
const char* Timing::MERCREDI = "Mercredi";
const char* Timing::JEUDI = "Jeudi";
const char* Timing::VENDREDI = "Vendredi";
const char* Timing::SAMEDI = "Samedi";
const char* Timing::DIMANCHE = "Dimanche";


Timing::Timing():Timing("Lundi",Temps(0,0),Temps(0,0)){}
Timing::Timing(const char *day,const Temps &T,const Temps &Y): jour(NULL){ setJour(day); setHeure(T);setDuree(Y); }
Timing::Timing(const Timing &T):Timing(T.getJour(), T.getHeure(), T.getDuree() ){}
Timing::~Timing(){/*cout << jour << endl*/; if(jour) delete jour; jour = NULL;}

void Timing::setJour(const char *d_day)
{    
    if(d_day){
        if(strcmp(d_day,LUNDI) == 0||
                strcmp(d_day,MARDI) == 0||
                    strcmp(d_day,MERCREDI)== 0||
                        strcmp(d_day,JEUDI)== 0||
                            strcmp(d_day,VENDREDI)== 0||
                                strcmp(d_day,SAMEDI)== 0||
                                    strcmp(d_day,DIMANCHE)== 0) 
                                    {   if(jour) delete jour;
                                        jour = new char [strlen(d_day)+1];
                                        strcpy(jour,d_day);
                                    }
                                    else
                                        throw TimingException(TimingException::JOUR_INVALIDE,"DAY_INPUT_ERROR");                                 
    }
}
void Timing::setHeure(const Temps &T){heure = T;}
void Timing::setDuree(const Temps &T){duree = T;}

Temps Timing::getHeure() const {return heure;}
Temps Timing::getDuree() const {return duree;}

const char* Timing::getJour() const{ return jour; }
void Timing::Affiche()
{ 
    std::cout  << "jour: " << jour << endl;
    std::cout << "heure: "; heure.Affiche();
    std::cout << "duree: "; duree.Affiche();
}

int Timing::operator<(const Timing &T){return compare(T) == -1;}
int Timing::operator>(const Timing &T){return compare(T) ==  1;}
int Timing::operator==(const Timing &T){return compare(T) == 0;}
int Timing::operator!=(const Timing &T){return !(*this == T);}
int Timing::operator<=(const Timing &T){return !(*this > T);}
int Timing::operator>=(const Timing &T){return !(*this < T);}

int Timing::compare(const Timing &T)
{
    int verif, verif2 = 0;

    if(strcmp(jour,LUNDI) == 0) verif = 1;
    else if(strcmp(jour,MARDI) == 0) verif = 2;
        else if(strcmp(jour,MERCREDI) == 0) verif = 3;
            else if(strcmp(jour,JEUDI) == 0) verif = 4;
                else if(strcmp(jour,VENDREDI) == 0) verif = 5;
                    else if(strcmp(jour,SAMEDI) == 0) verif = 6;
                        else if(strcmp(jour,DIMANCHE) == 0) verif = 7;

    if(strcmp(T.jour,LUNDI) == 0) verif2 = 1;
    else if(strcmp(T.jour,MARDI) == 0) verif2 = 2;
        else if(strcmp(T.jour,MERCREDI) == 0) verif2 = 3;
            else if(strcmp(T.jour,JEUDI) == 0) verif2 = 4;
                else if(strcmp(T.jour,VENDREDI) == 0) verif2 = 5;
                    else if(strcmp(T.jour,SAMEDI) == 0) verif2 = 6;
                        else if(strcmp(T.jour,DIMANCHE) == 0) verif2 = 7;

    if(verif < verif2) return -1;
    if(verif > verif2) return  1;

    if(heure < T.heure) return -1;
    if(duree > T.duree) return  1;

    return 0;
}


void Timing::Save(ofstream &fichier) const
{
    int size_of_jour(strlen(jour));

    fichier.write((char*)&size_of_jour,sizeof(int));
    fichier.write(jour,strlen(jour));
    //fichier.write((char*)&heure,sizeof(Temps));  
    //fichier.write((char*)&duree,sizeof(Temps));  

    heure.Save(fichier);
    duree.Save(fichier);
    
}

void Timing::Load(ifstream &fichier) 
{
    int size_of_jour;

    fichier.read((char*)&size_of_jour,sizeof(int));

    jour = new char [size_of_jour + 1];
    std::cout << "Timing::Load Sizejour=" << size_of_jour+1  << std::endl;
    fichier.read(jour,size_of_jour);
    jour[size_of_jour] = '\0';
    std::cout << "Timing::Load jour=" << jour  << std::endl;
    //fichier.read((char*)&heure,sizeof(Temps));  
    heure.Load(fichier);
    duree.Load(fichier);
    //fichier.read((char*)&duree,sizeof(Temps)); 
}

bool Timing::intersecte(const Timing& t)
{
    std::cout << std::endl << "Debut intersecte" << std::endl;
    if(this->getJour() == nullptr || t.getJour()== nullptr)
        TimingException(TimingException::AUCUN_TIMING,"Timing empty this or t->getjour() func");

    if(strcmp(this->getJour(), t.getJour()) == 0)
    {
        if(*this == t) //si le meme heure de debut
        {
            std::cout << "les 2 timing commencent à =" << this->getHeure() << std::endl;
            std::cout  << "Fin intersecte"<< std::endl << std::endl;
            return true; 
        }

        if(this->getHeure() < t.getHeure())
        {
            if((this->getHeure() + this->getDuree()) > t.getHeure())
            {
                std::cout << "timing: heure < t <heure+duree" << this->getHeure() << std::endl;
                std::cout  << "Fin intersecte"<< std::endl << std::endl;
                return true; 
            }
            return false;
        }
        if(this->getHeure() > t.getHeure())
        {
            if(this->getHeure() < (t.getHeure() + t.getDuree()) )
            {
                std::cout << "timing: t < heure < t+duree" << this->getHeure() << std::endl;
                std::cout  << "Fin intersecte"<< std::endl << std::endl;
                return true; 
            }
        }
        
        return false;
    }

    return false;
    std::cout  << "Fin intersecte"<< std::endl << std::endl;

    /*int verif, verif2 = 0;

    if(strcmp(jour,LUNDI) == 0) verif = 1;
    else if(strcmp(jour,MARDI) == 0) verif = 2;
        else if(strcmp(jour,MERCREDI) == 0) verif = 3;
            else if(strcmp(jour,JEUDI) == 0) verif = 4;
                else if(strcmp(jour,VENDREDI) == 0) verif = 5;
                    else if(strcmp(jour,SAMEDI) == 0) verif = 6;
                        else if(strcmp(jour,DIMANCHE) == 0) verif = 7;

    if(strcmp(t.jour,LUNDI) == 0) verif2 = 1;
    else if(strcmp(t.jour,MARDI) == 0) verif2 = 2;
        else if(strcmp(t.jour,MERCREDI) == 0) verif2 = 3;
            else if(strcmp(t.jour,JEUDI) == 0) verif2 = 4;
                else if(strcmp(t.jour,VENDREDI) == 0) verif2 = 5;
                    else if(strcmp(t.jour,SAMEDI) == 0) verif2 = 6;
                        else if(strcmp(t.jour,DIMANCHE) == 0) verif2 = 7;


    if(verif == verif2)
    {
        std::cout << "Timing.cpp >> verif == verif2" << std::endl;
        if(this->getHeure() == t.getHeure())
            {
                std::cout << "Timing.cpp >> this == t" << std::endl;
                return false;
            }
        if(this->getHeure() < t.getHeure())
        {    
            std::cout << "Timing.cpp >> this < t" << std::endl;
            if( !((this->getHeure()+this->getDuree()) <= t.getHeure()) )
            {
                std::cout << "Timing.cpp >> this+duree <= t" << std::endl;
                return false;
            }
            return true;
        }
        if(this->getHeure() > t.getHeure())
        {    
            std::cout << "Timing.cpp >> this > t" << std::endl;
            if( !(this->getHeure() >= (t.getHeure()+t.getDuree())) )
                return false;
        }
        return true;
    }
    if(verif > verif)
        return false;
    
    return true;*/
}