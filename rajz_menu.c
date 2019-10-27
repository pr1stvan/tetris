#include "header.h"

void lekerdezo_kirajzol(int a)
{
    SDL_Color feher = {255, 255, 255},piros={255,0,0},sarga={0,255,0};

    TTF_Font *font;
    SDL_Surface *felirat,*felirat2,*x,*y;
    SDL_Rect hova = { 0, 0, 0, 0 };
    char s[50];

    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 50);
    if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(2);
    }
    /*Mindent töröl a képről*/
    boxRGBA(kep,0,0,kep->w,kep->h,0,0,0,255);


    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 50);
    if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(2);
    }


    felirat = TTF_RenderUTF8_Blended(font,"méret beállítása" ,feher);

    hova.x=(kep->w-felirat->w)/2+1;
    SDL_BlitSurface(felirat, NULL, kep, &hova);


    sprintf(s,"%d",vilag.meretx);

    if(a==1)felirat = TTF_RenderUTF8_Blended(font,s,feher);
    else felirat=TTF_RenderUTF8_Shaded(font,s,sarga,piros);

    sprintf(s,"%d",vilag.merety);

    if(a==0)felirat2 = TTF_RenderUTF8_Blended(font,s,feher);
    else felirat2 = TTF_RenderUTF8_Shaded(font,s,sarga,piros);

    hova.x=(kep->w-(50+felirat->w+felirat2->w))/2+1;
    hova.y=(kep->h-felirat->h)/2+1;
    rectangleRGBA(kep,hova.x-2,hova.y,hova.x+felirat->w,hova.y+felirat->h,255,255,255,255);
    SDL_BlitSurface(felirat, NULL, kep, &hova);

    hova.y-=felirat->h+1;
    x=TTF_RenderUTF8_Blended(font,"X",feher);
    SDL_BlitSurface(x, NULL, kep, &hova);

    hova.y+=felirat->h+1;
    hova.x+=felirat->w+50;
    rectangleRGBA(kep,hova.x-2,hova.y,hova.x+felirat2->w,hova.y+felirat2->h,255,255,255,255);
    SDL_BlitSurface(felirat2, NULL, kep, &hova);

    hova.y-=felirat2->h+1;
    y=TTF_RenderUTF8_Blended(font,"Y",feher);
    SDL_BlitSurface(y, NULL, kep, &hova);

    /* a feliratot tartalmazo kepre nincs mar szukseg */
    SDL_FreeSurface(felirat2);
    SDL_FreeSurface(felirat);
    SDL_FreeSurface(y);
    SDL_FreeSurface(x);
    TTF_CloseFont(font);
    stringRGBA(kep, 420, kep->h-20, "Press esc to return", 255, 255, 255, 255);
    SDL_Flip(kep);
}

void menu_kirajzol(menu_allapot a)
{
    SDL_Color feher = {255, 255, 255}, piros={255,0,0},sarga={0,255,0};
    TTF_Font *font;
    SDL_Surface *felirat;
    SDL_Rect hova = { 0, 0, 0, 0 };
    int i;
    /*mindent töröl a képről*/
    boxRGBA(kep,0,0,kep->w,kep->h,0,0,0,255);

    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 50);
     if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(2);
     }

    for(i=0;i<=2;i++)
    {
        switch(i)
        {
            case 0:
            felirat = TTF_RenderUTF8_Blended(font,"új játék", feher);

            break;
            case 1:
            felirat = TTF_RenderUTF8_Blended(font,"eredmények", feher);

            break;
            case 2:
            felirat = TTF_RenderUTF8_Blended(font,"kilépés",feher);
            break;
        }
        hova.y=((kep->h-felirat->h*3)/2)+1+felirat->h*i;
        hova.x=((kep->w-felirat->w)/2)+1;
        SDL_BlitSurface(felirat, NULL, kep, &hova);
    }
    switch(a)
    {
        case uj_jatek:
        felirat = TTF_RenderUTF8_Shaded(font,"új játék", sarga,piros);

        break;
        case eredmenyek:
        felirat = TTF_RenderUTF8_Shaded(font,"eredmények", sarga,piros);

        break;
        case kilepes:
        felirat = TTF_RenderUTF8_Shaded(font,"kilépés",sarga,piros);
        break;
    }
    hova.y=((kep->h-felirat->h*3)/2)+1+felirat->h*a;
    hova.x=((kep->w-felirat->w)/2)+1;
    SDL_BlitSurface(felirat, NULL, kep, &hova);

    /* a feliratot tartalmazo kepre nincs mar szukseg */
    SDL_FreeSurface(felirat);
    TTF_CloseFont(font);
    SDL_Flip(kep);
}
/*リ*/
