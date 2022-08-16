#include <iostream>
#include <cstring>
#include "Event.h"
#include "Timing.h"
#include"Temps.h"
#include "TimingException.h"
#include <ostream>
#include <fstream>
using namespace std;

// : liste d'initialisation, permet d'initier les proprietes de mon objet.

  int Event::codeCourant = 0;

  Event::Event():Event(0,"default"){}  

  Event::Event(int cd, const char *SN ):Intitule(NULL),code(0),timing(NULL) { setIntitule(SN); setCode(cd); }  
    
  Event::Event(const Event &change):Event(change.getCode(),change.getIntitule()){}

  Event::~Event(){}
//voir pourquoi core dumped avec les deletes de variable dynamique
//if(timing) delete timing; if(Intitule) delete Intitule;

//fonctions qui affiche 
  Timing Event::getTiming() const 
  {
    if(timing) return *timing;
    else throw TimingException(TimingException::AUCUN_TIMING,"NO_TIMING_SET_ERROR");
  }

  int Event::getCode() const { return code; }

  const char* Event::getIntitule() const { return Intitule; }

  void Event::Affiche() const
  {
    std::cout << endl << "Code => " << code << endl;
    std::cout << "Intitule => " << Intitule << endl << endl;
    if(timing) timing->Affiche();
  }


  //fonction qui encode
  void Event::setCode(int cd) { if(cd >= 0) code = cd; }

  void Event::setIntitule(const char *SN)
  {    
    if(strlen(SN) > 128 or strlen(SN) <= 0){cerr << "Mot superieur a 128 caracteres" << endl; return;}
    if(Intitule) delete Intitule ;
    
    Intitule = new char [strlen(SN)+1];
    strcpy(Intitule,SN);
  }

  void Event::setTiming(const Timing &T){ if (timing) delete timing; timing = new Timing (T);}
  

  /*
  int code;
  char *Intitule;
  Timing *timing;
  */
  
  void Event::Save(ofstream &fichier) const
  {
    fichier.write((char*)&code,sizeof(int));
    int sizeInt = strlen(Intitule);
    fichier.write((char*)&sizeInt,sizeof(int));
    fichier.write(Intitule,sizeInt);

    //int i = strlen(timing->getJour());

    int sizeTim = (sizeof(*timing) /*+ i*/) /sizeof(Timing);
    fichier.write((char*)&sizeTim,sizeof(int));
    if(sizeTim > 0)
    {   
      timing->Save(fichier);   
      //fichier.write((char*)timing,sizeof(Timing));
    }
  }

  void Event::Load(ifstream &fichier)
  {
    fichier.read((char*)&code,sizeof(int));
    int sizeInt;
    fichier.read((char*)&sizeInt,sizeof(int));
    std::cout << "Event::Load sizeIntitule=" << sizeInt + 1 << std::endl;

    Intitule = new char[sizeInt+1];
    fichier.read(Intitule,sizeInt);
    Intitule[sizeInt] = '\0';

    std::cout << "Event::Load Intitule=" << Intitule << std::endl;

    int sizeTim;
    fichier.read((char*)&sizeTim,sizeof(int));
    std::cout << "Event::Load Timing present?=" << sizeTim << std::endl;

    timing = new Timing[sizeTim];
    if(sizeTim > 0)
    {     
      timing->Load(fichier);
      //fichier.read((char*)timing,sizeof(Timing));
    }
    
  }

