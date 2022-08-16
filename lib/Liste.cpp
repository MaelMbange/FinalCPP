#include <iostream>
#include "Liste.h"
#include "Professeur.h"
#include "Groupe.h"
#include "Local.h"
#include "Iterateur.h"
#include "Cours.h"
using namespace std;


template <class type> Cellule<type>::Cellule() : next_nodes(NULL){}

//compteur = 0;

template <class type> Liste<type>::Liste() : p_liste(NULL), compteur(0){}
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
    if(!p_liste) cerr << "La liste est vide. (Affiche)" << endl;
    else
    {
        Cellule <type> *recup_liste = p_liste;

        std::cout << "Debut affichage listeAffiche()" << endl << endl;
        while (recup_liste)
        {
            std::cout << recup_liste->valeur << endl;
            recup_liste = recup_liste->next_nodes;
        }
        std::cout << endl << "Fin affichage" << endl << endl;
    }
}
template <class type> void Liste<type>::insere(const type &val)
{
    compteur++;

    if(!p_liste)
    {
        p_liste = new Cellule <type>;
        p_liste->valeur = val;
    }
    else
    {
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
        std::cerr << "Liste vide" << endl;
        return NULL;
    }
    if (ind < 0 || ind > compteur-1)
    {
        std::cerr << "error indicateur" << endl;
        return NULL;
    }

    i = ind;
    while(i)
    {
        //std::cerr << "on navigue : valeur=" <<ret->valeur << std::endl;
        //std::cerr << "Valeur de i=" << i <<std::endl;
        ret = ret->next_nodes;
        i--;
    }
    std::cerr << "fin navigation" <<std::endl;
    return ret;
}

template <class type> type Liste<type>::retire(int ind)
{    
    Cellule <type> *to_del_element;
    Cellule <type> *before; // recupere le prochain element
    Cellule <type> *after;// recupere l'element avant l'element à supprimer
    type back_val;
    
    if (ind == 0)// si on est au debut
    {
        std::cerr << "ind == 0" << std::endl;
        to_del_element = p_liste;
        if(p_liste->next_nodes != NULL)
        {
            p_liste = p_liste->next_nodes;
            //to_del_element->next_nodes = nullptr;
        }
        else
            p_liste = nullptr;            
        back_val = to_del_element->valeur;
    }
    else if (ind == compteur-1) // si on est à la fin
    {
        std::cerr << "ind == compteur-1" << std::endl;
        before = nav(ind-1);
        to_del_element = nav(ind);

        before->next_nodes = NULL;
        back_val = to_del_element->valeur;
    }
    else if(ind < compteur-1) // cas où on est ni au debut ni à la fin 
    {
        //std::cerr << "ind < compteur-1" << std::endl;
        to_del_element = nav(ind); 
        //std::cerr << "Element to del=" << to_del_element->valeur <<std::endl;
        before = nav(ind-1); //std::cerr << "before to del=" << before->valeur <<std::endl;
        after = nav(ind+1); //std::cerr << "after to del=" << after->valeur <<std::endl;

        before->next_nodes = after;
        back_val = to_del_element->valeur;
        
    }
    delete to_del_element;
    compteur--;
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

template<class type> bool Liste<type>::operator==(const Liste<type>& L2) const
{
    Iterateur<type> it{*this},it2{L2};

    for(it.reset(),it2.reset();!it.end();it++,it2++)
    {
        if( !(((type)(it)) == ((type)(it2))) ) return false;
    }

    return true;
}
template<class type> bool Liste<type>::operator!=(  Liste<type>& L2) 
{
    return !(*this == L2);
}

template<class type> bool Liste<type>::operator<( Liste<type>& L2) 
{
    Iterateur<type> iterator{*this},iterator2{L2};

    iterator.reset();
    iterator2.reset();

    for(;!iterator.end();)
    {
        if(! (((type)(iterator)) < ((type)(iterator2))) ) return false;

        iterator++;
        iterator2++;
    }

    return true;
}
template<class type> bool Liste<type>::operator>( Liste<type>& L2) 
{
    return (L2 < *this);
}

template<class type> bool Liste<type>::operator<=( Liste<type>& L2) 
{
    return !(*this>L2);
}
template<class type> bool Liste<type>::operator>=( Liste<type>& L2) 
{
    return !(*this<L2);
}

template<class type> Cellule<type>* Liste<type>::getPliste() const
{
    return p_liste;
}


template class Liste<int>;
template class Liste<Professeur>;
template class Liste<Groupe>;
template class Liste<Local>;
template class Liste<Cours>;