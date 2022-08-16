#ifndef __PLAN_H__
#define __PLAN_H__


class Planifiable
{
    protected:    
        int id;
        char *txt;
        
    public:
        //voir copy s'il faut
        Planifiable();
        Planifiable(int i);
        Planifiable(const Planifiable &P);
        ~Planifiable();
        
        virtual const char* Txt() = 0;
        virtual const char* Tuple() = 0;

        void setId(const int i);
        int getId() const;  
        static int idCourant;   
};

#endif