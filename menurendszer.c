#include "header.h"

int menurendszer()
{
    SDL_Event esemeny;
    int megy_a_menu=1,gombora=0,gomb_figyelo=0;
    /*billenytyûzet kezelõ változók*/
    int fel=0,le=0,enter=0,esc=0;
    menu_allapot a=0;
    menu_gomb_allapot g_a=semmi;

    menu_kirajzol(a);
    while(megy_a_menu)
    {
       SDL_WaitEvent(&esemeny);
       switch(esemeny.type)
       {
            case SDL_KEYDOWN:
            switch(esemeny.key.keysym.sym)
            {
                case SDLK_RETURN:
                enter=1;
                break;
                case SDLK_ESCAPE:
                esc=1;
                break;
                case SDLK_UP:
                fel=1;
                break;
                case SDLK_DOWN:
                le=1;
                break;
            }
            break;
            case SDL_KEYUP:
             switch(esemeny.key.keysym.sym)
            {
                case SDLK_RETURN:
                enter=0;
                break;
                case SDLK_ESCAPE:
                esc=0;
                break;
                case SDLK_UP:
                fel=0;
                break;
                case SDLK_DOWN:
                le=0;
                break;

            }
            break;
            case SDL_QUIT:
            megy_a_menu=0;
            return 0;
            break;
            case SDL_USEREVENT:

            gomb_figyelo=le-fel;
                    switch(g_a)
                    {
                        case semmi:
                        if(gomb_figyelo==-1){g_a=var_fel;gombora=0;}
                        if(gomb_figyelo==1){g_a=var_le;gombora=0;}
                        break;
                        case var_le:
                            switch(gomb_figyelo)
                            {
                                case 1:
                                gombora++;
                                if(gombora==3)
                                {
                                    gombora=0;
                                    g_a=foly_le;
                                }
                                gomb_figyelo=0;
                                break;
                                case -1:
                                gombora=0;
                                gomb_figyelo=-1;
                                g_a=var_fel;
                                break;
                                case 0:gombora=0;g_a=semmi;gomb_figyelo=0;
                                break;
                            }
                            break;
                        case var_fel:
                            switch(gomb_figyelo)
                            {
                                case -1:
                                gombora++;
                                if(gombora==3)
                                {
                                    gombora=0;
                                    g_a=foly_fel;
                                }
                                gomb_figyelo=0;
                                break;
                                case 1:
                                gombora=0;
                                gomb_figyelo=1;
                                g_a=var_le;
                                break;
                                case 0:gombora=0;g_a=semmi;gomb_figyelo=0;
                                break;
                            }
                            break;
                        case foly_le:
                            switch(gomb_figyelo)
                            {
                                case 1:
                                break;
                                case -1:
                                g_a=var_fel;
                                gombora=0;
                                break;
                                case 0:
                                gombora=0;
                                g_a=semmi;

                                break;
                            }
                            break;
                         case foly_fel:
                            switch(gomb_figyelo)
                            {
                                case -1:
                                break;
                                case 1:
                                g_a=var_le;
                                gombora=0;
                                break;
                                case 0:
                                gombora=0;
                                g_a=semmi;

                                break;
                            }
                            break;
                    }
            switch(a)
            {
                case uj_jatek:
                if(enter==1)
                {

                    return 1;

                }
                if(gomb_figyelo==-1)a=kilepes;
                if(gomb_figyelo==1)a=eredmenyek;
                break;
                case eredmenyek:
                /*enter esetén kiiratja az eredményeket majd elfelejti, hogy entert nyomott a felhasználó*/
                if(enter)
                {

                    high_score();
                    enter=0;
                }
                a+=gomb_figyelo;
                break;
                case kilepes:
                if(enter==1)return 0;
                if(gomb_figyelo==-1)a=eredmenyek;
                if(gomb_figyelo==1)a=uj_jatek;
                break;
            }



            menu_kirajzol(a);
            if(esc==1)return 0;

            break;
       }


    }


    return 1;
}
