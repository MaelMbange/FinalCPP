#include <iostream>
#include "Exception.h"
#include <cstring>
using namespace std;

Exception::Exception() {}

Exception::Exception(const char *msg)
{
	/*cerr << "Constructeur Exception" << endl;*/
	if(msg){ message = new char[strlen(msg)+1]; strcpy(message,msg); }
	else cerr << "message non valide" << endl;
}

Exception::~Exception() { if(message) delete(message); /*cerr << "destructeur Exception" << endl;*/}

Exception::Exception(const Exception &E) : Exception(E.message) {/* cerr << "destructeur Exception" << endl;*/}

int Exception::getCode() const { }

const char* Exception::getmessage() const {return message;}