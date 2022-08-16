#include <iostream>
#include "Iterateur.h"
#include "Professeur.h"
#include "Groupe.h"
#include "Local.h"
#include "Cours.h"



template<class type> Iterateur<type>::Iterateur(const Liste<type> &LI):L(LI), ptr(LI.getPliste())
{
    //cerr << "constructeur iterateur" << endl;
}
template<class type> Iterateur<type>::~Iterateur()
{
    //cerr << "destructeur iterateur" << endl;
}


template<class type> bool Iterateur<type>::end(){ return ptr == 0; }
template<class type> void Iterateur<type>::reset(){ptr = L.getPliste();}
template<class type> bool Iterateur<type>::operator++()
{
    if(ptr)
    {
        ptr = ptr->next_nodes;
        return true;
    }
    else return false;
}
template<class type> bool Iterateur<type>::operator++(int){return operator++();}
template<class type> Iterateur<type>::operator type() const 
{
    return ptr->valeur;
}


template class Iterateur<int>;
template class Iterateur<Professeur>;
template class Iterateur<Groupe>;
template class Iterateur<Local>;
template class Iterateur<Cours>;