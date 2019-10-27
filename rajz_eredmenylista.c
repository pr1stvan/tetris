#include "header.h"

void pontlista_kirajzol(pontlista *lis)
{
    SDL_Color feher = {255, 255, 255};
    SDL_Rect nev_hova = { 0, 0, 0, 0 },szam_hova = { 0, 0, 0, 0 };
    TTF_Font *font;
    SDL_Surface *nev[11];
    SDL_Surface *szam[11];
    char s[50];






    int limit, max;
    pontlista *e;
    int i;
    int nev_meretx,szam_meretx,merety;

    boxRGBA(kep, 0, 0, kep->w,kep->h, 0, 0, 0, 255);

    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 36);


    nev[0] = TTF_RenderUTF8_Blended(font, "Név", feher);
    szam[0]=TTF_RenderUTF8_Blended(font, "pontszám", feher);
    i=1;





    if(lis!=NULL){
    limit=lis->psz;
    for(e=lis;e!=NULL;e=e->kov)if(e->psz>limit)limit=e->psz;
    i=1;
    for(e=lis;e!=NULL;e=e->kov)if(e->psz==limit)
    {
        sprintf(s,"%d. %s",i,e->nev);
        nev[i]=TTF_RenderUTF8_Blended(font, s, feher);
        sprintf(s,"%d",e->psz);
        szam[i]=TTF_RenderUTF8_Blended(font, s, feher);
        i++;
    }
    while(i<=10)
    {
        for(e=lis;e!=NULL;e=e->kov)
        {
            if(e->psz<limit)
            {
                max=e->psz;
                break;
            }
        }
        if(e==NULL)break;
        while(e!=NULL)
        {
            if(e->psz>max && e->psz<limit)max=e->psz;
            e=e->kov;
        }
        for(e=lis;e!=NULL && i<=10;e=e->kov)
        {
            if(e->psz==max)
            {
                sprintf(s,"%d. %s",i,e->nev);
                nev[i]=TTF_RenderUTF8_Blended(font, s, feher);
                sprintf(s,"%d",e->psz);
                szam[i]=TTF_RenderUTF8_Blended(font, s, feher);
                i++;
            }
        }
        limit=max;
    }}
    /*Maradék képek 0-val töltõdnek ki*/
    while(i<=10)
    {

        sprintf(s,"%d.",i);
        nev[i]=TTF_RenderUTF8_Blended(font, s, feher);
        sprintf(s,"%d",0);
        szam[i]=TTF_RenderUTF8_Blended(font, s, feher);
        i++;
    }


    nev_meretx=nev[0]->w;
    for(i=0;i<=10;i++)
    {
        if(nev[i]->w>nev_meretx)nev_meretx=nev[i]->w;
    }
    szam_meretx=szam[0]->w;
    for(i=0;i<=10;i++)
    {
        if(szam[i]->w>szam_meretx)szam_meretx=szam[i]->w;
    }

    /*Egységes y-méret, hogy egy sorban legyenek*/
    merety=nev[0]->h;
    for(i=0;i<=10;i++)
    {
        if(nev[i]->h>merety)merety=nev[i]->h;
        if(szam[i]->h>merety)merety=nev[i]->h;
    }



    nev_hova.x=(kep->w-nev_meretx-szam_meretx-50)/2+2;

    szam_hova.y=nev_hova.y=(kep->h-10*merety)/2+2;
    szam_hova.x=nev_hova.x+nev_meretx+50;


    /*A tényleges kirajzolás*/
    for(i=0;i<=10;i++)
    {
        SDL_BlitSurface(nev[i], NULL, kep, &nev_hova);
        SDL_BlitSurface(szam[i], NULL, kep, &szam_hova);
        nev_hova.y+=merety;
        szam_hova.y+=merety;
    }

    stringRGBA(kep, 390, kep->h-20, "Press esc or enter to return", 255, 255, 255, 255);
    for(i=0;i<=10;i++)
    {
        SDL_FreeSurface(nev[i]);
        SDL_FreeSurface(szam[i]);
    }

    TTF_CloseFont(font);
    SDL_Flip(kep);
    return;
}
/*物*/
