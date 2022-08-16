#ifndef __LT_H__
#define __LT_H__
#include "Liste.h"



template <class type> class ListeTriee : public Liste<type>
{
    public:
        ListeTriee();
        ListeTriee(const ListeTriee &val);
        ListeTriee(const Liste<type> &LT);
        ~ListeTriee();
        
        void insere(const type &val);
};



#endif