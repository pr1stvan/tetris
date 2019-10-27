#include "header.h"
/*Forrás:https://infoc.eet.bme.hu/sdl.php*/



/* Beolvas egy szoveget a billentyuzetrol.
 * Ehhez rajzol egy zold keretet x, y, sz, m helyen, 'hatter' szinnel
 * es 'szin' szinu betukkel.
 * A rajzolashoz hasznalt font es a kepernyo surface-e az utolso parameterek.
 * Az elso a tomb, ahova a beolvasott szoveg kerul.
 * A visszateresi erteke logikai igaz, ha sikerult a beolvasas.
 * Ha nem kell UNICODE text, akkor a dest tipusa char * legyen, a
 * TTF_RenderUNICODE_Blended() fuggvenyhivas pedig TTF_RenderText_Blended-re cserelheto. */
int input_text(Uint16 *dest, int x, int y, int sz, int m,
               SDL_Color hatter, SDL_Color szin, TTF_Font *font, SDL_Surface *screen,int tombmeret) {
    SDL_Rect cel = { x, y, sz, m };
    SDL_Surface *felirat;
    SDL_Event event;
    int hossz, kilep, enter;
    int i=0;

    /*Ezt a részt hozzáírtam*/
    felirat = TTF_RenderUTF8_Blended(font,"Név:", szin);
    cel.y-=40;
    boxRGBA(screen,0,0,screen->w,screen->h,0,0,0,255);
    SDL_BlitSurface(felirat, NULL, screen, &cel);
    SDL_Flip(screen);
    cel.y+=40;
    SDL_FreeSurface(felirat);



    hossz = 0;
    dest[hossz] = 0x0000;   /* lezaro 0 */
    SDL_EnableUNICODE(1);
    enter = 0;
    kilep = 0;
    while (!kilep && !enter) {
        /* szoveg kirajzolasa */
        boxRGBA(screen, x, y, x+sz-1, y+m-1, hatter.r, hatter.g, hatter.b, 255);
        felirat = TTF_RenderUNICODE_Blended(font, dest, szin);
        SDL_BlitSurface(felirat, NULL, screen, &cel);
        SDL_FreeSurface(felirat);
        rectangleRGBA(screen, x, y, x+sz-1, y+m-1, 0, 255, 0, 255);
        /* updaterect: mint az sdl_flip, de csak a kepernyo egy darabjat */
        SDL_UpdateRect(screen, x, y, sz, m);

        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.unicode) {
                    case 0x0000:
                        /* nincs neki megfelelo karakter (pl. shift gomb) */
                        break;
                    case '\r':
                    case '\n':
                        /* enter: bevitel vege */
                        enter = 1;
                        break;
                    case '\b':
                        /* backspace: torles visszafele, ha van karakter */
                        if (hossz>0)
                            {dest[--hossz] = 0x0000;i--;}
                        break;
                    default:
                        /* karakter: tombbe vele, plusz lezaro nulla */
                        if(i<=tombmeret-1)
                        {dest[hossz++] = event.key.keysym.unicode;
                        dest[hossz] = 0x0000;i++;}
                        break;
                }
                break;
            case SDL_QUIT:
                /* visszatesszuk a sorba ezt az eventet, mert
                 * sok mindent nem tudunk vele kezdeni */
                SDL_PushEvent(&event);
                kilep = 1;
                break;
        }
    }

    /* 1 jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
    return enter;
}

/*Eredetileg az infoc-n ez volt a main függvény*/
int nevbekeres(char *s) {
    SDL_Color feher = {255, 255, 255}, fekete = { 0, 0, 0 };
    Uint16 szoveg[50];
    TTF_Font *font;


    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 32);
    if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(2);
    }
    SDL_EnableKeyRepeat(500, 30);

    /* szoveg beolvasasa */
    /*maximum 20 karakter*/
    input_text(szoveg, (kep->w-400)/2+1, (kep->h-40)/2+1, 400, 40, fekete, feher, font, kep,21);
    unicode_to_utf8(szoveg, s);

    TTF_CloseFont(font);

    return 0;
}
/*メー*/
