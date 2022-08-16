#ifndef __ITE_H__
#define __ITE_H__
#include "Liste.h"


template <class type> class Iterateur
{
    private:
        const Liste<type> &L;
        const Cellule<type> *ptr;

    public:
        Iterateur(const Liste<type> &LI);
        ~Iterateur();


        bool end();
        void reset();
        bool operator++();
        bool operator++(int);
        operator type() const;
};


#endif