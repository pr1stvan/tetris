#include "header.h"

void high_score()
{
    SDL_Event esemeny;
    pontlista *lis=NULL;


    lis=pontlista_init(lis);
    pontlista_kirajzol(lis);

    while(1)
    {
        SDL_WaitEvent(&esemeny);
         if(esemeny.type==SDL_KEYDOWN)
        {

            switch(esemeny.key.keysym.sym)
            {
                case SDLK_RETURN:
                pontlista_felszab(lis);
                return;
                case SDLK_ESCAPE:

                pontlista_felszab(lis);

                return;
            }
        }
    }

}
