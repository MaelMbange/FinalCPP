#ifndef __TIMINGEXC_H__
#define __TIMINGEXC_H__
#include "Exception.h"

class TimingException : public Exception
{
    private:
        int code;
    
    public:    
        TimingException();
        TimingException(int cd, const char* desc);
        TimingException(const TimingException& TE);
        ~TimingException();

        static const int JOUR_INVALIDE, AUCUN_TIMING;
        int getCode() const;
};



#endif 