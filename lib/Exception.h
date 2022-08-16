#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__


class Exception
{
	protected:	
		char *message;

	public:
		Exception();
		
		Exception(const char *msg);

		Exception(const Exception &E);

		virtual~Exception();

		virtual int getCode() const;
		const char * getmessage() const;		
};


#endif