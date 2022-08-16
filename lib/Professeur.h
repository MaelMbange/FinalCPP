#ifndef __PROF_H__
#define __PROF_H__
#include "planifiable.h"
#include <iostream>
#include <ostream>
#include <fstream>
using namespace std;


class Professeur : public Planifiable
{
    friend ostream& operator<<(ostream& os,const Professeur &P);

    private:
        char *nom;
        char *prenom;
        int compare(const Professeur &prof);
    public:

        Professeur();
        Professeur(const int i,const char* name,const char* S_name);
        Professeur(const Professeur &P);
        ~Professeur();

        void setNom(const char *Name);
        void setPrenom(const char *S_Name);

        const char *getNom() const ;
        const char *getPrenom() const;

        Professeur& operator=(const Professeur &P); 
        int operator<(const Professeur &prof);
        int operator>(const Professeur &prof);
        int operator==(const Professeur &prof);

        const char* Txt();
        const char *Tuple();

        void Save(ofstream &fichier) const;
        void Load(ifstream &fichier);

};


#endif