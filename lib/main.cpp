#include "Cours.h"
#include "Event.h"
#include "Timing.h"
#include "Temps.h"
#include "Liste.h"
#include <iostream>


int main()
{
    Cours c_Liste[10];

    for(Cours& c: c_Liste)
    {
        c.Affiche();
    }


    return 0;
}