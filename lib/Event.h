#ifndef __Test1_H__
#define __Test1_H__
#include "Timing.h"
#include"Temps.h"

class Event
{
private:
  int code;
  char *Intitule;
  Timing *timing;
  static int codeCourant;
  
public:
  Event();
  Event(int cd, const char *SN );
  Event(const Event &change);
  ~Event();
  Timing getTiming() const;
  int getCode() const ;
  const char* getIntitule() const;
  void Affiche() const;
  void setIntitule(const char *SN);
  void setCode(int cd);
  void setTiming(const Timing &T);

  

  virtual void Save(ofstream &fichier) const;
  virtual void Load(ifstream &fichier);

};

#endif