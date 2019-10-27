#include "header.h"

/*SDL timer kezelő függvény*/
Uint32 idozit(Uint32 ms, void* param)
{
    SDL_Event esemeny;
    esemeny.type = SDL_USEREVENT;
    SDL_PushEvent(&esemeny);
    return ms;
}

int main(int argc,char *argv[])
{

   /*A játék részei*/


    vilag.meretx=10;
    vilag.merety=20;




    /*Az SDL indítása*/
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    kep=SDL_SetVideoMode(1024,768,0,SDL_ANYFORMAT);
      if (!kep)
      {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
      }
    SDL_WM_SetCaption("Tetris", "Tetris");
    id = SDL_AddTimer(50, idozit, NULL);
    /*Véletlenszám generátor inicializálás*/
    srand(time(0));

    /*Ha a menürendszer nem jelez kilépést, indul a játék, majd újraindul a menürendszer*/
    while(menurendszer())
    {


        if(meret_lekerdez()==0)
        jatek();
    }
    /*Kilépés*/
    SDL_RemoveTimer(id);
    SDL_Quit();
    return 0;

}
