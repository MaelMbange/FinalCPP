#ifndef __GRP_H__
#define __GRP_H__
#include "planifiable.h"
#include <ostream>
#include <fstream>
using namespace std;


class Groupe : public Planifiable
{
    //friend ostream& operator<<(ostream& os,const Groupe& G);

    private:

        int numero;
        int compare(const Groupe &grp);
    public:

        Groupe();
        Groupe(const int id,const int i);
        Groupe(const Groupe &G);
        ~Groupe();

        void setNumero(const int i);
        int getNumero() const;

        Groupe& operator=(const Groupe &G);
        int operator==(const Groupe &grp);
        int operator>(const Groupe &grp);
        int operator<(const Groupe &grp);

        const char* Txt();
        const char *Tuple();

        void Save(ofstream &fichier) const;
        void Load(ifstream &fichier);

        friend ostream& operator<<(ostream& os,const Groupe& grp)  ;

};


#endif