#include <iostream>
#include "ListeTriee.h"
#include "Liste.h"
#include "Professeur.h"
#include "Groupe.h"
#include "Local.h"
#include "Cours.h"

using namespace std;



template <class type> ListeTriee<type>::ListeTriee() {cerr << "constructeur Liste Triee"  << endl;}
template <class type> ListeTriee<type>::~ListeTriee(){ cerr << "destructeur Liste Triee" << endl;}
template <class type> ListeTriee<type>::ListeTriee(const ListeTriee &LT)
{ 
    if(LT.estVide() == true) cerr << "Il n'y a rien à copier" << endl;
    else
    {        
        Cellule <type> *recup2 = LT.p_liste;

        while (recup2)
        {
            insere(recup2->valeur);
            recup2 = recup2->next_nodes;
        }        
    }
}

template <class type> ListeTriee<type>::ListeTriee(const Liste<type> &LT)
{ 
    if(LT.estVide() == true) cerr << "Il n'y a rien à copier" << endl;
    else
    {        
        Cellule <type> *recup2 = LT.getPliste();

        while (recup2)
        {
            insere(recup2->valeur);
            recup2 = recup2->next_nodes;
        }        
    }
}

template <class type> void ListeTriee<type>::insere(const type &val)
{

    Cellule<type> *Pnew = new Cellule<type>;
    Cellule<type> *ptr,*p;

    Pnew->valeur = val;

    if(this->p_liste == NULL)// si la liste est vide
    {
        std::cerr << "listeTrie vide" <<std::endl;
        this->p_liste = Pnew;
        this->compteur++;
        return;
    }

    std::cerr << "listeTrie contient element" <<std::endl;
    bool found = false;
    ptr = this->p_liste;

    while((ptr != NULL) && !found)// on parcoure
    {
        if(Pnew->valeur < ptr->valeur)
        {
            found = true; // si valeur ajoutée est plus petite retourner true
            std::cerr << "listeTrie valeur < a ptr->valeur" <<std::endl;
        }
        else ptr = ptr->next_nodes;
    }

    if(!found) // si c'est faux
    {
        std::cerr << "listeTrie Pas Inferieur" <<std::endl;
        p = this->p_liste;
        while(p->next_nodes != NULL) p = p->next_nodes;
        p->next_nodes = Pnew;
        this->compteur++;
        return;
    }

    if(ptr == this->p_liste)
    {
        std::cerr << "listeTrie Element avant liste" <<std::endl;
        Pnew->next_nodes = this->p_liste;
        this->p_liste = Pnew;
        this->compteur++;
        return;
    }

    std::cerr << "listeTrie Element dans la liste" <<std::endl;
    p = this->p_liste;
    while (p->next_nodes != ptr) p = p->next_nodes;
    Pnew->next_nodes = ptr;
    p->next_nodes = Pnew;
    this->compteur++;
}


template class ListeTriee<int>;
template class ListeTriee<Professeur>;
template class ListeTriee<Groupe>;
template class ListeTriee<Local>;
template class ListeTriee<Cours>;