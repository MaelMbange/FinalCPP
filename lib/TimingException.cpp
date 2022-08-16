#include <iostream>
#include "TimingException.h"
#include "Exception.h"
using namespace std;

const int TimingException::JOUR_INVALIDE = 0;
const int TimingException::AUCUN_TIMING = 0;

TimingException::TimingException(){}
TimingException::TimingException(int cd, const char* desc) : Exception(desc), code(cd) {}
TimingException::TimingException(const TimingException& TE){}
TimingException::~TimingException(){}

int TimingException::getCode()const {return code;}