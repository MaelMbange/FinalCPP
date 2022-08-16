#ifndef __TIME_H__
#define __TIME_H__
#include <iostream>
#include "TempsException.h"
using namespace std;

class Temps
{

    friend Temps operator+(const Temps &T, int i);
    friend Temps operator+(int i,const Temps &T);
    friend Temps operator-(const Temps &T, int i);
    friend Temps operator-(int i,const Temps &T);
    friend Temps operator+(const Temps &T,const Temps &Y);
    friend Temps operator-(const Temps &T,const Temps &Y);
    
    friend ostream& operator<< (ostream& s,const Temps& T); 
    friend istream& operator>> (istream& s, Temps& T);

    private:
        int heure;
        int minute;
        int compare(const Temps &T);
    public:
        Temps();
        Temps(const int i);
        Temps(const int hour, const int min);
        Temps(const Temps &horaire);
        ~Temps();

        void setHeure(int hour);
        void setMinute(int min);
        int getHeure() const;
        int getMinute() const;
        int getAllTime();
        void Affiche();        
        
        Temps& operator=(const Temps &T);
        int operator<(const Temps &T);
        int operator>(const Temps &T);
        int operator<=(const Temps &T);
        int operator>=(const Temps &T);
        int operator==(const Temps &T);
        Temps& operator++();
        Temps operator++(int);
        Temps& operator--();
        Temps operator--(int);

        void Save(ofstream &fichier) const;
        void Load(ifstream &fichier);
};



#endif