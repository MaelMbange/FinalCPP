#include <iostream>
#include "TempsException.h"
#include <cstring>
using namespace std;


const int TempsException::HEURE_INVALIDE = 0; 
const int TempsException::MINUTE_INVALIDE = 1; 
const int TempsException::DEPASSEMENT = 2; 
const int TempsException::FORMAT_INVALIDE = 3;

TempsException::TempsException() {/*cerr << "constructeur par defaut" << endl;*/}

TempsException::TempsException(int cd,const char* msg) : Exception(msg), code(cd){ /*cerr << "Constructeur TempsException" << endl;*/ } 

TempsException::TempsException(const TempsException &TE){ /*cerr << "TempsException copy" << endl*/;}

TempsException::~TempsException(){ /*cerr << "destructeur TempsException" << endl; */}

int TempsException::getCode() const {return code;}