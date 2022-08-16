#ifndef __LIST_H__
#define __LIST_H__

template <class type> struct Cellule
{
    type valeur;
    Cellule<type> *next_nodes;
    Cellule();
};

template <class type> class Iterateur;

template <class type> class Liste
{   
    protected:
        Cellule <type> *p_liste;
        int compteur;
        void clear_all();
        Cellule<type> * nav(int ind);

    public:
        Liste();
        Liste(const Liste<type> &L);
        ~Liste();        

        bool estVide() const;
        int getNombreElements() const;
        void Affiche() const;
        virtual void insere(const type &val);
        type retire(int ind);
        
        Liste<type> &operator=(const Liste<type> &Li);
        bool operator==(const Liste<type>& L2) const;
        bool operator!=( Liste<type>& L2) ;

        bool operator<=( Liste<type>& L2) ;
        bool operator>=( Liste<type>& L2) ;
        bool operator<( Liste<type>& L2) ;
        bool operator>( Liste<type>& L2) ;

        Cellule<type>* getPliste() const;


        friend class Iterateur<type>;
};

#endif