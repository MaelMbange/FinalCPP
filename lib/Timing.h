#ifndef __TIMING_H__
#define __TIMING_H__
#include "Temps.h"

class Timing
{
    private:
        char *jour;
        Temps heure;
        Temps duree;
        int compare(const Timing &T);
    public:
        Timing();
        Timing(const char *day,const Temps &T,const Temps &Y);
        Timing(const Timing &t_timing);
        ~Timing();

        void setJour(const char *d_day);
        void setHeure(const Temps &T);
        void setDuree(const Temps &T);

        Temps getHeure() const;
        Temps getDuree() const;
        const char* getJour() const;
        void Affiche();

        int operator<(const Timing &T);
        int operator>(const Timing &T);
        int operator==(const Timing &T);
        int operator!=(const Timing &T);
        int operator<=(const Timing &T);
        int operator>=(const Timing &T);
        

        static const char* LUNDI;
        static const char* MARDI;
        static const char* MERCREDI;
        static const char* JEUDI;
        static const char* VENDREDI;
        static const char* SAMEDI;
        static const char* DIMANCHE;

        void Save(ofstream &fichier) const;
        void Load(ifstream &fichier);

        bool intersecte(const Timing& t);
};



#endif