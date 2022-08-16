#ifndef __LOC_H__
#define __LOC_H__
#include "planifiable.h"
#include <ostream>
#include <fstream>
using namespace std;



class Local : public Planifiable
{

    friend ostream& operator<<(ostream& os,const Local& L);

    private:
        char *nom;
        int compare(const Local &loc);
    public:

        Local();
        Local(const int i,const char *Name);
        Local(const Local &L);
        ~Local();

        void setNom(const char *Name);
        const char* getNom() const;
        Local& operator=(const Local &L);
        int operator==(const Local &loc);
        int operator>(const Local &loc);
        int operator<(const Local &loc);

        const char* Txt();
        const char *Tuple();
        
        void Save(ofstream &fichier) const;
        void Load(ifstream &fichier);
};


#endif