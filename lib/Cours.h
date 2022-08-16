#ifndef COURS_H
#define COURS_H

#include <cstring>
#include <iostream>
#include "Event.h"
#include "Liste.h"
#include "ListeTriee.h"
#include "Iterateur.h"
#include <ostream>
#include <fstream>

class Cours : public Event
{
private:
    int idProfesseur;
    int idLocal;
    ListeTriee<int> idGroupes;


public:
    Cours();
    Cours(const int idProf,const int idLocal,const Liste<int> idGroupe);
    Cours(const char * intit,const int idProf,const int idLocal,const Liste<int>& idGroupe);
    Cours(const Cours&);
    ~Cours();

    void setIdProfesseur(const int& id_ );
    void setIdLocal(const int& id_ );
    void setListeIdGroupe(const Liste<int>& liste_);

    int getIdProfesseur() const ;
    int  getIdLocal() const ;
    const Liste<int>& getListeIdGroupe() const;

    Cours& operator=(const Cours& cours2);

    bool operator==(const Cours& C2) const ; //le compilateur ne les veut pas en constant
    bool operator!=(const Cours& C2) const ; // pourquoi ?!  je ne sais pas 
    bool operator<(const  Cours& C2) const ; //surement car c'est une vm d'oracle XD
    bool operator<=(const Cours& C2) const ;
    bool operator>(const  Cours& C2) const ;
    bool operator>=(const Cours& C2) const ;

    void ajouteIdGroupe(int id);
    bool contientIdGroupe(int id);

    friend ostream& operator<<(ostream& os, const Cours& crs_);

    static int compteur_Cours;

    virtual void Save(ofstream &fichier) const /*override*/;
    virtual void Load(ifstream &fichier) /*override*/;
};

#endif