#include "header.h"

void jatek()
{
     /*SDL kezelő változók*/
    SDL_Event esemeny;


    /*A játekmenetet figyelõ vátltozók*/
    int up=0,down=0,left=0, right=0;
    int megy_a_jatek=1;

    int ora=0;

    int gombora=0;
    int gomb_figyelo;
    allapot allapot=alap;
    int lehet;
    int lehet_oldalra;
    int forog=0;
    int le=0;
    int kov_elem;
   /*játék kezelő változók*/

    elem *e=NULL;
    int i,j;

    pont hely;int kockameret;
    /*Pontszám kimentéshez változók*/
    char jatekos_nev[50];
    int pontszam=0;
    FILE *f;
   /*A játék részei*/
    elem *lista_eleje=NULL;

    /*A játék előtt névbekérés*/
    nevbekeres(jatekos_nev);
    f=fopen("high_score.txt","at");
    if (f==NULL) {
    return;
    }


    jatek_kirajzol(&hely,&kockameret);
    kov_elem=rand()%7;
    kov_elem_rajz(hely,kockameret,kov_elem);
    pontkiir(hely,kockameret,pontszam);

    /*Esemény kezelés*/
    while(megy_a_jatek)
    {
        SDL_WaitEvent(&esemeny);
        switch(esemeny.type)
        {

            /*Billenytyűzet figyelő változók beállíása.*/
            case SDL_KEYDOWN:
                switch(esemeny.key.keysym.sym)
                {
                 case SDLK_UP:up=1;
                 forog=1;
                 break;
                 case SDLK_DOWN:down=1;
                 le=1;
                 break;
                 case SDLK_LEFT:left=1;
                 break;
                 case SDLK_RIGHT: right=1;
                 break;
                 case SDLK_RETURN:
                 forog=1;
                 break;
                 case SDLK_ESCAPE:
                 megy_a_jatek=0;
                 fprintf(f,"%s(%dx%d) %d\n",jatekos_nev,vilag.meretx,vilag.merety,pontszam);
                 fclose(f);
                 return;
                 break;

                }
                break;
            case SDL_KEYUP:
                switch(esemeny.key.keysym.sym)
                {
                    case SDLK_UP:up=0;
                    break;
                    case SDLK_DOWN:down=0;
                    break;
                    case SDLK_LEFT:left=0;
                    break;
                    case SDLK_RIGHT:right=0;
                    break;
                }
                break;


            case SDL_USEREVENT:
                /*Lefelé mozgatás*/
                if(ora==6)
                {
                      ora=0;
                      /*első*/
                      if(lista_eleje==NULL)
                      {
                          lista_eleje=object_beszur(lista_eleje,kov_elem);
                          kov_elem=rand()%7;
                          kov_elem_rajz(hely,kockameret,kov_elem);
                      }
                      else
                      {
                          lehet=1;
                          for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                          {
                              if((e->y>=vilag.merety-1 || van_elem(lista_eleje,e->x,e->y+1))&&e->iranyithato)lehet=0;
                          }

                          if(lehet)
                          {
                              for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                              if(e->iranyithato)e->y+=1;
                          }
                          else/*Ha nem lehet lefelé mozgatni beszúr új elemeket és ha egy sor üsszegyűlik törli*/
                          {
                              for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                                 {
                                    e->iranyithato=0;
                                 }

                              for(i=0;i<vilag.merety;i++)
                                {
                                    if(sortelevan(lista_eleje,i))
                                    {
                                        /*A pontszámnak integerben kell tárolódnia*/
                                        if(pontszam<=2147483647-100)pontszam+=100;
                                        pontkiir(hely,kockameret,pontszam);
                                        lista_eleje=sortorol(lista_eleje,i);
                                    }
                                }
                              for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                              {
                                  if(e->iranyithato==0 && e->y<=-1)
                                  {
                                      lista_felszabadit(lista_eleje);
                                      fprintf(f,"%s(%dx%d) %d\n",jatekos_nev,vilag.meretx,vilag.merety,pontszam);
                                     fclose(f);
                                     game_over();
                                      return;
                                  }
                              }
                              lista_eleje=object_beszur(lista_eleje,kov_elem);
                              kov_elem=rand()%7;
                              kov_elem_rajz(hely,kockameret,kov_elem);
                          }
                      }
                }
                else ora++;


                /*forgatás*/
                if(forog==1)
                {
                    forgat(lista_eleje);
                    forog=0;
                }


                /*Azonnali ejtés a lefelé gomb megnyomásával*/
                if(le==1)
                {

                    int ltav;
                    int ty[vilag.meretx];
                    elem *aktivak[4];

                    i=0;
                    for(e=lista_eleje;e!=NULL && i<4;e=e->kovetkezo)
                    {
                        if(e->iranyithato)
                        {
                            aktivak[i]=e;
                            i++;
                        }
                    }


                    if(i>=4){

                    for(i=0;i<vilag.meretx;i++)
                    {
                        /*Ennél biztos nagyobb*/
                        int legnagyobb_aktiv_y=-5;
                        /*első*/
                        for(j=0;j<4;j++)
                        {
                            if(aktivak[j]->x==i && aktivak[j]->y>legnagyobb_aktiv_y)legnagyobb_aktiv_y=aktivak[j]->y;
                        }
                        ty[i]=vilag.merety;

                        for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                        {

                            if(ty[i]>e->y && e->x==i && e->iranyithato==0 && e->y>legnagyobb_aktiv_y)
                            {
                                ty[i]=e->y;
                            }
                        }
                    }

                    /*megkeresi az elso iranyithatot*/
                    e=aktivak[0];

                    ltav=ty[aktivak[0]->x]-aktivak[0]->y;


                    for(i=0;i<4;i++)
                    {
                        if(ty[aktivak[i]->x]-aktivak[i]->y<ltav)
                        ltav=ty[aktivak[i]->x]-aktivak[i]->y;
                    }

                    for(i=0;i<4;i++)
                    {
                        aktivak[i]->y+=ltav-1;
                        aktivak[i]->iranyithato=0;
                    }

                    /*Ha kitöltődik egy sor törölni kell*/
                    for(i=0;i<vilag.merety;i++)
                    {
                        if(sortelevan(lista_eleje,i))
                        {
                            lista_eleje=sortorol(lista_eleje,i);
                            /*A pontszámnak integerben kell tárolódnia*/
                            if(pontszam<=2147483647-100)pontszam+=100;
                            pontkiir(hely,kockameret,pontszam);
                        }
                    }
                    /*Ha ekkor egy nem irányítható elem nincs a pályán, játék vége*/

                    for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                    {
                        if(e->iranyithato==0 && e->y<=-1)
                        {
                            lista_felszabadit(lista_eleje);
                            fprintf(f,"%s(%dx%d) %d\n",jatekos_nev,vilag.meretx,vilag.merety,pontszam);
                            fclose(f);
                            game_over();
                            return;
                        }

                    }

                    lista_eleje=object_beszur(lista_eleje,kov_elem);
                    kov_elem=rand()%7;
                    kov_elem_rajz(hely,kockameret,kov_elem);
                    le=0;
                    }
                }

                /*oldalra mozgatás*/
                /*Ezek a sorok a nem azonnal folyamatos mozgatáshoz kellenek*/
                gomb_figyelo=right-left;
                    switch(allapot)
                    {
                        case alap:
                        if(gomb_figyelo==-1){allapot=var_bal;gombora=0;}
                        if(gomb_figyelo==1){allapot=var_jobb;gombora=0;}
                        break;
                        case var_jobb:
                            switch(gomb_figyelo)
                            {
                                case 1:
                                gombora++;
                                if(gombora==3)
                                {
                                    gombora=0;
                                    allapot=folyamatos_jobb;
                                }
                                gomb_figyelo=0;
                                break;
                                case -1:
                                gombora=0;
                                gomb_figyelo=-1;
                                allapot=var_bal;
                                break;
                                case 0:gombora=0;allapot=alap;gomb_figyelo=0;
                                break;
                            }
                            break;
                        case var_bal:
                            switch(gomb_figyelo)
                            {
                                case -1:
                                gombora++;
                                if(gombora==3)
                                {
                                    gombora=0;
                                    allapot=folyamatos_bal;
                                }
                                gomb_figyelo=0;
                                break;
                                case 1:
                                gombora=0;
                                gomb_figyelo=1;
                                allapot=var_jobb;
                                break;
                                case 0:gombora=0;allapot=alap;gomb_figyelo=0;
                                break;
                            }
                            break;
                        case folyamatos_jobb:
                            switch(gomb_figyelo)
                            {
                                case 1:
                                break;
                                case -1:
                                allapot=var_bal;
                                gombora=0;
                                break;
                                case 0:
                                gombora=0;
                                allapot=alap;

                                break;
                            }
                            break;
                         case folyamatos_bal:
                            switch(gomb_figyelo)
                            {
                                case -1:
                                break;
                                case 1:
                                allapot=var_jobb;
                                gombora=0;
                                break;
                                case 0:
                                gombora=0;
                                allapot=alap;

                                break;
                            }
                            break;
                    }
                    /*először meg kell nézni,hogy lehet-e oldalra menni*/
                    lehet_oldalra=1;
                    for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                    {
                        if((e->x+gomb_figyelo>=vilag.meretx || e->x+gomb_figyelo<0 || van_elem(lista_eleje,e->x+gomb_figyelo,e->y))&& e->iranyithato)
                           lehet_oldalra=0;
                    }
                    if(lehet_oldalra)
                    {
                        for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
                        {
                            if(e->iranyithato)e->x+=gomb_figyelo;
                        }
                    }
                elem_kirajzol(lista_eleje,hely,kockameret);

                break;
            case SDL_QUIT:
                megy_a_jatek=0;
                break;

        }
    }
/*Kilépés*/
lista_felszabadit(lista_eleje);
fprintf(f,"%s(%dx%d) %d\n",jatekos_nev,vilag.meretx,vilag.merety,pontszam);
fclose(f);
return;
}
