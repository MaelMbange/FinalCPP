#include "Cours.h"


int Cours::compteur_Cours = 1;

Cours::Cours() : Event(compteur_Cours,"default")
{
    setIdProfesseur(0);
    setIdLocal(0);
    //compteur_Cours++;
}

Cours::Cours(const char * intit,const int idProf_,const int idLocal_,const Liste<int>& idGroupe_) : Event(compteur_Cours,intit)
{
    setIdLocal(idLocal_);
    setIdProfesseur(idProf_);
    setListeIdGroupe(idGroupe_);
    //compteur_Cours++;
}

Cours::Cours(const Cours& c2) : Cours(c2.getIntitule(),c2.idProfesseur,c2.idLocal,c2.idGroupes)
{
    setTiming(c2.getTiming());
    setCode(c2.getCode());
}
Cours::~Cours(){}

Cours& Cours::operator=(const Cours& cours2)
{
    idProfesseur = cours2.idProfesseur;
    idLocal = cours2.idLocal;
    idGroupes = cours2.idGroupes;
    setCode(cours2.getCode());
    setIntitule(cours2.getIntitule());
    setTiming(cours2.getTiming());

    return *this;
}

bool Cours::operator==(const Cours& C2) const
{
    //if(this->idProfesseur != C2.idProfesseur) return false;
    //if(this->idLocal != C2.idLocal) return false;
    //if(this->idGroupes != C2.idGroupes) return false;
    if(this->getTiming() != C2.getTiming()) return false;

        return true;
}
bool Cours::operator!=(const Cours& C2) const
{
    return !(*this == C2);
}
bool Cours::operator<(const Cours& C2) const
{
    //if(!(this->idProfesseur < C2.idProfesseur)) return false;
    //if(!(this->idLocal < C2.idLocal)) return false;
    //if(!(this->idGroupes < C2.idGroupes)) return false;
    if(!(this->getTiming() < C2.getTiming())) return false;

    return true;
}
bool Cours::operator<=(const Cours& C2) const
{
    return !(*this > C2);
}
bool Cours::operator>(const Cours& C2) const
{
    return (C2 < *this);
}
bool Cours::operator>=(const Cours& C2) const
{
    return !(*this < C2);
}

/* Accesseurs et mutateurs*/

void Cours::setIdProfesseur(const int& id_ )
{
    idProfesseur = id_;
}
void Cours::setIdLocal(const int& id_ )
{
    idLocal = id_;
}
void Cours::setListeIdGroupe(const Liste<int>& liste_)
{
    idGroupes = liste_;
}

int Cours::getIdProfesseur() const
{
    return idProfesseur;
}
int  Cours::getIdLocal() const
{
    return idLocal;
}
const Liste<int>& Cours::getListeIdGroupe() const
{
    return idGroupes;
}



/*methode spe prof*/

void Cours::ajouteIdGroupe(int id)
{
    idGroupes.insere(id);
}
bool Cours::contientIdGroupe(int id)
{
    Iterateur<int> it = idGroupes;

    for(it.reset();!it.end();it++)
    {
        if( ((int)(it)) == id) return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Cours& crs_)
{
    os << "Hello! this is Cours class" ;
    return os;
}

void Cours::Save(ofstream &fichier) const 
{
    Event::Save(fichier);

    fichier.write((char*)&idProfesseur,sizeof(int));
    fichier.write((char*)&idLocal,sizeof(int));
    int getValue = idGroupes.getNombreElements();
    fichier.write((char*)&getValue,sizeof(int));

    Iterateur<int> grp = idGroupes;

    for(grp.reset();!grp.end();grp++)
    {
        int i = (int)grp;
        fichier.write((char*)&i,sizeof(int));
    }


}
void Cours::Load(ifstream &fichier) 
{
    Event::Load(fichier);

    fichier.read((char*)&idProfesseur,sizeof(int));
    fichier.read((char*)&idLocal,sizeof(int));

    int getElement;
    fichier.read((char*)&getElement,sizeof(int));
    Cours::compteur_Cours = getElement;

    std::cout << "Cours::Lecture idProfesseur=" << idProfesseur << std::endl;
    std::cout << "Professeur::Lecture idlocal=" << idLocal << std::endl;
    std::cout << "Cours::Load element recuperé grp = " << getElement << std::endl;

    for(int i = 0;i<getElement;i++)
    {
        int valeur_cur;
        fichier.read((char*)&valeur_cur,sizeof(int));
        std::cout << "Professeur::Lecture groupe=" << valeur_cur << std::endl;
        idGroupes.insere(valeur_cur);
    }
    std::cout << "Cours::fin Load Cours" << std::endl;
}