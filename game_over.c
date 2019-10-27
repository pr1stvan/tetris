#include "header.h"

void game_over()
{
    SDL_Event esemeny;
    SDL_Surface *felirat;
    SDL_Color piros = {255, 0,0};
    SDL_Rect hova = { 0, 0, 0, 0 };
    TTF_Font *font;




    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 100);
     if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(2);
     }
    boxRGBA(kep,0,0,kep->w,kep->h,0,0,0,255);
    felirat= felirat = TTF_RenderUTF8_Blended(font, "GAME OVER", piros);

    hova.x=(kep->w-felirat->w)/2+1;
    hova.y=(kep->h-felirat->h)/2+1;

    SDL_BlitSurface(felirat, NULL, kep, &hova);
    stringRGBA(kep, 390, kep->h-20, "Press esc or enter to return", 255, 255, 255, 255);
    SDL_Flip(kep);
    TTF_CloseFont(font);
    SDL_FreeSurface(felirat);
    while(1)
    {
        SDL_WaitEvent(&esemeny);
         if(esemeny.type==SDL_KEYDOWN)
        {

            switch(esemeny.key.keysym.sym)
            {
                case SDLK_RETURN:

                return;
                case SDLK_ESCAPE:


                return;

            }
        }
    }
}

