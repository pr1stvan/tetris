#include "header.h"

/*Az elemek kirajzol�sa*/
void elem_kirajzol(elem*lista,pont hely,int m)
{
    elem *e;

    /*El�sz�r t�rl�s*/
    boxRGBA(kep, hely.x, hely.y, hely.x+m*vilag.meretx-1,hely.y+m*vilag.merety-1, 0, 0, 0, 255);

    /*elemek kirajzol�sa*/
    for(e=lista;e!=NULL;e=e->kovetkezo)
    {
        if(e->y>=0)boxRGBA(kep, hely.x+m*e->x+1,hely.y+m*e->y+1, hely.x+m*e->x+m-2,hely.y+m*e->y+m-2, e->szin1,e->szin2,e->szin3, 255);
    }
    SDL_Flip(kep);
}

void pontkiir(pont hely,int m,int pontszam)
{
    SDL_Color feher = {255, 255, 255};
    TTF_Font *font;
    SDL_Surface *felirat;
    SDL_Rect hova = { 0, 0, 0, 0 };
    char pont_sztring[50];


    sprintf(pont_sztring,"%d",pontszam);


    if(hely.y+4*36+36-10+36>hely.y+m*vilag.merety)
    {
         hely.y+=m*vilag.merety+36-10;
    }
    else
    {
        hely.x+=m*vilag.meretx+36+2;
        hely.y+=4*36+36-10;
    }
     /*A pontsz�m ki�r�sa*/
    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 36);
     if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(2);
    }
    felirat = TTF_RenderUTF8_Blended(font,pont_sztring, feher);
     rectangleRGBA(kep, hely.x-1, hely.y-1, hely.x+felirat->w+2, hely.y+36, 255, 255, 255, 255);
     /*Az el�z� pontsz�m t�rl�se*/
     boxRGBA(kep, hely.x, hely.y, hely.x+felirat->w-1, hely.y+36-1, 0, 0, 0, 255);


    hova.x=hely.x;hova.y=hely.y-2;
   SDL_BlitSurface(felirat, NULL, kep, &hova);
    /* a feliratot tartalmazo kepre nincs mar szukseg */
    SDL_FreeSurface(felirat);

    TTF_CloseFont(font);
    SDL_Flip(kep);
}

/*oldalra a k�vetkez� elem kirajzol�sa*/
void kov_elem_rajz(pont hely,int m, int id)
{
    pont e[4];
    int i,R=0,G=0,B=0,szin=rand()%3;


    hely.x+=m*vilag.meretx+36+2;

    /*V�letlen sz�n*/
    switch(szin)
    {
        case 0:
        R=255;
        break;
        case 1:G=255;
        break;
        case 2:B=255;
        break;
    }
    rectangleRGBA(kep, hely.x-1, hely.y-1, hely.x+3*36, hely.y+4*36, 255, 255, 255, 255);
    boxRGBA(kep, hely.x,hely.y, hely.x+3*36-1, hely.y+4*36-1, 0, 0, 0, 255);
   switch(id)
        {
            case 0:
            for(i=0;i<=2;i++)
            {
                e[i].x=1;e[i].y=i;
            }
            e[3].x=2;e[3].y=2;
            break;
            case 1:
            e[0].x=2;e[0].y=0;
            e[1].x=2;e[1].y=1;
            e[2].x=1;e[2].y=1;
            e[3].x=1;e[3].y=2;
            break;
            case 2:
            for(i=0;i<=2;i++)
            {
                e[i].x=1;e[i].y=i;
            }
            e[3].x=0;e[3].y=2;
            break;
            case 3:
            e[0].x=0;e[0].y=0;
            e[1].x=0;e[1].y=1;
            e[2].x=1;e[2].y=1;
            e[3].x=1;e[3].y=2;
            break;
            case 4:
            e[0].x=0;e[0].y=1;
            e[1].x=1;e[1].y=0;
            e[2].x=1;e[2].y=1;
            e[3].x=2;e[3].y=1;
            break;
            case 5:
            e[0].x=0;e[0].y=1;
            e[1].x=0;e[1].y=2;
            e[2].x=1;e[2].y=1;
            e[3].x=1;e[3].y=2;
            break;
            case 6:
            e[0].x=1;e[0].y=0;
            e[1].x=1;e[1].y=1;
            e[2].x=1;e[2].y=2;
            e[3].x=1;e[3].y=3;
            break;
        }

    for(i=0;i<4;i++)
    {
        boxRGBA(kep,hely.x+36*e[i].x+1, hely.y+36*e[i].y+1, hely.x+36*e[i].x+36-2,hely.y+36*e[i].y+36-2,R, G, B, 255);
    }
    SDL_Flip(kep);
}
/*ind�t�s ut�n rajzolja ki a j�t�kot*/
void jatek_kirajzol(pont *hely,int *kockameret)
{
    int kepx=663,kepy=728;

    hely->x=21;
    hely->y=21;


    /*rectangleRGBA(kep, hely->x-2, hely->y-2, hely->x+kepx+1,hely->y+kepy+1, 230, 130, 30, 255);*/
    /*mindent t�r�l a k�pr�l*/
    boxRGBA(kep,0,0,kep->w,kep->h,0,0,0,255);
    if((double)vilag.meretx/vilag.merety>=(double)kepx/kepy)
    {
       /*v�zszintes fesz�t�s*/
        (*kockameret)=kepx/vilag.meretx;
        hely->y=(kepy-vilag.merety*(*kockameret))/2+hely->y;
        /*k�z�pre teszi a k�pet*/
        hely->x+=(kepx-(*kockameret)*vilag.meretx)/2;
    }
    else
    {
        /*f�gg�leges fesz�t�s*/
        (*kockameret)=kepy/vilag.merety;
        hely->x=(kepx-vilag.meretx*(*kockameret))/2+hely->x;
        /*k�z�pre teszi a k�pet*/
        hely->y+=(kepy-(*kockameret)*vilag.merety)/2;
    }
    rectangleRGBA(kep, hely->x-1, hely->y-1, hely->x+vilag.meretx*(*kockameret),hely->y+vilag.merety*(*kockameret), 255, 255,255, 255);


    SDL_Flip(kep);
}
