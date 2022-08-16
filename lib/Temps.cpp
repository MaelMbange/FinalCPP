#include "Temps.h"
#include <iostream>
#include "TempsException.h"
#include <cstring>
#include <ostream>
#include <fstream>
using namespace std;

Temps::Temps():Temps(0,0){}
Temps::Temps(const int i)
{
    if(i <= 1439 && i >= 0){heure = i/60; minute = i%60;}
    else throw TempsException(TempsException::DEPASSEMENT,"DEPASSEMENT_ERROR");    
}
Temps::Temps(const int hour, const int min) { setHeure(hour); setMinute(min); }
Temps::Temps(const Temps &horaire): Temps( horaire.getHeure(), horaire.getMinute() ){}
Temps::~Temps(){}

void Temps::setHeure(int hour)
{   
    if(!(hour < 0 || hour > 24)) heure = hour;
    else throw TempsException(TempsException::HEURE_INVALIDE,"HOUR_ERROR");
}

void Temps::setMinute(int min)
{   
    if(!(min < 0 || min > 60)) minute = min; 
    else throw TempsException(TempsException::MINUTE_INVALIDE,"MINUTES_ERROR"); 
}

int Temps::getHeure() const{ return heure; }
int Temps::getMinute() const{ return minute; }
int Temps::getAllTime(){return 60*heure + minute;}
void Temps::Affiche()   { if (minute < 10) std::cout << heure << "h0" << minute << endl; else std::cout << heure << "h" << minute << endl; }

Temps& Temps::operator=(const Temps &T) {heure = T.heure;minute = T.minute; return *this; }

//=====
Temps operator+(int i,const Temps &T){return T + i;}//mettre des constantes 
Temps operator-(int i,const Temps &T){return i - 60*T.heure - T.minute;}//car sinon compilateur kiff pas.
Temps operator+(const Temps &T, int i)
{
    if(i < 0)return T - i;
    return Temps(60*T.heure + T.minute + i);
}
Temps operator-(const Temps &T, int i)
{
    if(i < 0)return T + (-i);
    return Temps(60*T.heure + T.minute - i);
}
Temps operator+(const Temps &T,const Temps &Y){return Temps(60*(T.heure + Y.heure) + T.minute + Y.minute);}
Temps operator-(const Temps &T,const Temps &Y){return Temps(60*(T.heure - Y.heure) + T.minute - Y.minute);}

Temps& Temps::operator++(){*this = *this + 30;return *this;}
Temps Temps::operator++(int){Temps tempo(*this);*this = *this + 30;return tempo;}
Temps& Temps::operator--(){*this = *this - 30;return *this;}
Temps Temps::operator--(int){Temps tempo(*this);*this = *this - 30;return tempo;}

//=====
int Temps::operator<(const Temps &T){return compare(T) == -1;}
int Temps::operator>(const Temps &T){return compare(T) ==  1;}
int Temps::operator<=(const Temps &T){return !(*this > T);}
int Temps::operator>=(const Temps &T){return !(*this < T);}
int Temps::operator==(const Temps &T){return compare(T) == 0;}
int Temps::compare(const Temps &T)
{
    if(heure < T.heure) return -1;
    if(heure > T.heure) return  1;

    if(minute < T.minute) return -1;
    if(minute > T.minute) return  1;

    return 0;
}

ostream& operator<< (ostream& s,const Temps& T)
{
    if(T.minute < 10) s << T.heure << "h0" << T.minute;
    else  s << T.heure << "h" << T.minute;

    return s;
}   
istream& operator>> (istream& s, Temps& T)
{
    char time[6];
    char verif;
    int h,m(0);
    int max_size;
    int j(0);

    cout << "Entrez un horaire : --H-- " << endl;
    s >> time;
    max_size = strlen(time);
    //cout << endl;   

    if(max_size != 5 && max_size != 4) throw TempsException(TempsException::FORMAT_INVALIDE,"FORMAT_ERROR_1");

    
    for(int i = 0; i < max_size && j <= 1; i++)
    {
        if (isalpha(time[i]))
        {
            verif = time[i];
            j++;
        }        
    }
    if (j != 1 || (verif != 'h' && verif != 'H'))   
    {
       throw TempsException(TempsException::FORMAT_INVALIDE,"FORMAT_ERROR_2");
    }
    /*if (verif != 'h' && verif != 'H')
    {
        throw TempsException(TempsException::FORMAT_INVALIDE,"FORMAT_ERROR_3");
    }*/
    else if(max_size == 5)T = Temps(atoi(time),atoi(&time[3])); // ou alors sscan
    else T = Temps(atoi(time),atoi(&time[2])); // ou alors sscan
    

    return s;
}


void Temps::Save(ofstream &fichier) const
{
    fichier.write((char*)this,sizeof(Temps));
}

void Temps::Load(ifstream &fichier)
{
    fichier.read((char*)this,sizeof(Temps));
    
    std::cout << "Temps::Load temps=" <<  *this << std::endl;  
}