#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include <string.h>
#include <math.h>

#include "enum_struct.h"
#include "menu.h"
#include "rajz_menu.h"
#include "elemlista.h"
#include "rajz_jatek.h"
#include "jatek.h"
#include "eredmenylista.h"
#include "rajz_eredmenylista.h"
#include "ora.h"
#include "infoc_fuggvenyek.h"

/*Ezeket minden programrész látja, main-be inicializálódnak*/
world vilag;
SDL_Surface *kep;
SDL_TimerID id;



#endif // HEADER_H_INCLUDED
