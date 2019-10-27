#include "header.h"



int meret_lekerdez()
{
    SDL_Event esemeny;

    int a=0;
    int enter=0,esc=0,fel=0,le=0;
    menu_gomb_allapot g_a=semmi;
    int gombora=0,gomb_figyelo=0;


    vilag.meretx=10;
    vilag.merety=20;
    while(1)
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
                case SDLK_LEFT:
                if(a==1)a=0;
                break;
                case SDLK_RIGHT:
                if(a==0)a=1;
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
            return 1;
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
                case 0:
                if(vilag.meretx>1 && gomb_figyelo==1)vilag.meretx-=gomb_figyelo;
                if(vilag.meretx<200 && gomb_figyelo==-1)vilag.meretx-=gomb_figyelo;
                break;
                case 1:
                if(vilag.merety>1 && gomb_figyelo==1)vilag.merety-=gomb_figyelo;
                if(vilag.merety<200 && gomb_figyelo==-1)vilag.merety-=gomb_figyelo;
                break;
            }
            lekerdezo_kirajzol(a);
            if(esc)return 1;
            if(enter)return 0;
            break;
       }
    }
}
