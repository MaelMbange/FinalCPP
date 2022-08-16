#include <iostream>
#include "planifiable.h"

int Planifiable::idCourant = 0;

Planifiable::Planifiable() : Planifiable(0) 
{
    //idCourant++;
}
Planifiable::Planifiable(int N_id):id(0),txt(NULL) 
{
    setId(N_id);
    //idCourant++;
}
Planifiable::Planifiable(const Planifiable &P) : Planifiable(P.getId()) {}
Planifiable::~Planifiable()
{
    delete txt;
    //idCourant--;
}

void Planifiable::setId(const int i) {if(i >= 0 ) id = i;}
int Planifiable::getId() const {return id;}
