#ifndef __TEMPSEXC_H__
#define __TEMPSEXC_H__
#include "Exception.h"


class TempsException : public Exception
{
	private:
		int code;

	public: 
		TempsException();
		TempsException(int cd, const char *msg);
		TempsException(const TempsException &TE);
		~TempsException();

		int getCode() const override;

		static const int HEURE_INVALIDE; 
		static const int MINUTE_INVALIDE; 
		static const int DEPASSEMENT; 
		static const int FORMAT_INVALIDE;
};

#endif