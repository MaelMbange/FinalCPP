#include <iostream>
#include "Liste.h"
#include "Professeur.h"
#include "Groupe.h"
#include "Local.h"
using namespace std;


template <class type> Cellule<type>::Cellule() : next_nodes(NULL){}

//compteur = 0;

template <class type> Liste<type>::Liste() : p_liste(nullptr), compteur(0){}
template <class type> Liste<type>::Liste(const Liste<type> &L) : Liste()
{
    if(L.estVide() == true) cerr << "Il n'y a rien à copier" << endl;
    else
    {        
        Cellule <type> *recup2 = L.p_liste;

        while (recup2)
        {
            insere(recup2->valeur);
            recup2 = recup2->next_nodes;
        }        
    }
} // dupliquer avec operator=
template <class type> Liste<type>::~Liste(){cerr << "Appel du destructeur" <<  endl; clear_all();} // definir clear_all

template <class type> bool Liste<type>::estVide() const 
{
    std::cout<< "valeur de p_liste (estVide)=" << p_liste->valeur <<std::endl;

    if(!p_liste) 
        return true;
    return false;
}
template <class type> int Liste<type>::getNombreElements() const 
{
    return compteur;
}
template <class type> void Liste<type>::Affiche() const 
{
    if(estVide()) cerr << "La liste est vide. (Affiche)" << endl;
    else
    {
        Cellule <type> *recup_liste = p_liste;

        cerr << "Debut affichage " << endl << endl;
        while (recup_liste)
        {
            std::cout << recup_liste->valeur << endl;
            recup_liste = recup_liste->next_nodes;
        }
        cerr << endl << "Fin affichage" << endl << endl;
    }
}
template <class type> void Liste<type>::insere(const type &val)
{
    compteur++;

    if(!p_liste)
    {
        std::cout << "liste vide - on insert la premiere valeur" << std::endl;
        p_liste = new Cellule <type>;
        p_liste->valeur = val;
    }
    else
    {
        std::cout << "liste contient deja un element - ajout a la suite" <<std::endl;
        Cellule <type> *recup_liste;

        for (recup_liste = p_liste; recup_liste->next_nodes; recup_liste = recup_liste->next_nodes)
        {}
        recup_liste->next_nodes = new Cellule<type>;
        recup_liste->next_nodes->valeur = val;
    }
}

template <class type> Cellule<type> * Liste<type>::nav(int ind)  
{
    Cellule <type> *ret = p_liste;
    int i;

    if (estVide() == true) // si la liste est vide on sort
    {
        cerr << "Liste vide" << endl;
        return NULL;
    }
    if (ind < 0 || ind > compteur-1)
    {
        cerr << "error indicateur" << endl <<"valeur indicateur" <<ind << std::endl;
        return NULL;
    }

    i = ind;
    while(i)
    {
        ret = ret->next_nodes;
        i--;
    }
    return ret;
}

template <class type> type Liste<type>::retire(int ind) 
{    
    Cellule <type> *to_del_element;
    Cellule <type> *before; // recupere le prochain element
    Cellule <type> *after;// recupere l'element avant l'element à supprimer
    type back_val;
    
    std::cout << std::endl << "RETIRE : indice=" << ind << std::endl;

    if (ind == 1)// si on est au debut
    {
        to_del_element = p_liste;
        if(p_liste->next_nodes != NULL)
        {
            p_liste = p_liste->next_nodes;
            back_val = to_del_element->valeur;
        }
    }
    else if (ind == compteur-1) // si on est à la fin
    {
        before = nav(ind-1);
        to_del_element = nav(ind);

        before->next_nodes = NULL;
        back_val = to_del_element->valeur;
    }
    else if(ind < compteur-1) // cas où on est ni au debut ni à la fin 
    {
        to_del_element = nav(ind);
        before = nav(ind-1);
        after = nav(ind+1);

        before->next_nodes = after;
        back_val = to_del_element->valeur;
        
    }
    delete to_del_element;
    compteur--;
    if(estVide()== true) std::cout << "est vide " << std::endl;
    return back_val;       
}
template <class type> void Liste<type>::clear_all()
{    
    if (estVide() == true)
    {
        cerr << "la liste est vide" << endl;
    }
    else
    {
        compteur = 0;

        Cellule <type> *recup = p_liste;

        while(estVide() == false)
        {
            p_liste = p_liste->next_nodes;
            delete recup;
            recup = p_liste;
        }
        cerr << "la liste a ete nettoyee" << endl;
    }    

}

template <class type> Liste <type> & Liste<type>::operator=(const Liste<type> &Li)
{
    clear_all();    

    if(Li.estVide() == true) cerr << "Il n'y a rien à copier" << endl;
    else
    {
        Cellule <type> *recup2 = Li.p_liste;

        while (recup2)
        {
            insere(recup2->valeur);
            recup2 = recup2->next_nodes;
        }        
    }
    return (*this);
}




template class Liste<int>;
template class Liste<Professeur>;
template class Liste<Groupe>;
template class Liste<Local>;