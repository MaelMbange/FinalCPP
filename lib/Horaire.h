#ifndef __HORAIRE_H__
#define __HORAIRE_H__

#include "ListeTriee.h"
#include "Professeur.h"
#include "Groupe.h"
#include "Local.h"
#include "Liste.h"
#include "Iterateur.h"
#include "planifiable.h"
#include "Cours.h"
#include <ostream>
#include <istream>
#include <fstream>
#include <string>
#include <cstdlib>

class Horaire
{
    private:
        ListeTriee<Professeur> Professeurs;
        ListeTriee<Groupe> Groupes;
        ListeTriee<Local> Locaux;
        ListeTriee<Cours> Cours_;
        
    public:
        Horaire();
        ~Horaire();
        Horaire& operator=(const Horaire& hor);

        void ajouteProfesseur(const char* nom,const char* prenom);
        void afficheProfesseurs();
        void supprimeProfesseurParIndice(int ind);
        void supprimeProfesseurParId(int id);

        void ajouteGroupe(int numero);
        void afficheGroupes();
        void supprimeGroupeParIndice(int ind);
        void supprimeGroupeParId(int id);

        void ajouteLocal(const char* nom);
        void afficheLocaux();
        void supprimeLocalParIndice(int ind);
        void supprimeLocalParId(int ind);

        void supprimeCoursParId(int id);

        const Liste<Professeur>& getlisteProfesseurs()const;
        const Liste<Groupe>& getlisteGroupe()const;
        const Liste<Local>& getlisteLocaux()const;
        const Liste<Cours>& getlisteCours()const;

        Liste<Professeur>& getlisteProfesseurs();
        Liste<Groupe>& getlisteGroupe();
        Liste<Local>& getlisteLocaux();
        Liste<Cours>& getlisteCours();

        bool professeurDisponible(int id,const Timing& timing);
        bool groupeDisponible(int id,const Timing& timing);
        bool localDisponible(int id,const Timing& timing);
        void planifie(Cours& c,const Timing& t);

        const char* getTuple(const Cours& c);
        const char* getTuple2(const Cours& c);

        void Save(const char* nomFichier);
        void Load(const char* nomFichier);

        void importeProfesseurs(const char* nomFichier);
        void importeGroupes(const char* nomFichier);
        void importeLocaux(const char* nomFichier);

        void exporteHoraireProfesseur(int id);
        void exporteHoraireGroupe(int id);
        void exporteHoraireLocal(int id);
};



#endif