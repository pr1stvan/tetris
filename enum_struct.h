#ifndef ENUM_STRUCT_H_INCLUDED
#define ENUM_STRUCT_H_INCLUDED

typedef enum menu_allapot{uj_jatek=0,eredmenyek,kilepes}menu_allapot;
typedef enum beallitasok_allapot{x,y}beallitasok_allapot;
typedef enum menu_gomb_allapot{semmi,var_le,foly_le,var_fel,foly_fel} menu_gomb_allapot;
typedef enum allapot{alap,var_bal,var_jobb,folyamatos_bal,folyamatos_jobb}allapot;

typedef struct elem{int x,y,iranyithato;char szin1,szin2,szin3;struct elem *elozo;struct elem *kovetkezo;}elem;
typedef struct pontlista{char *nev;int psz; struct pontlista *kov;}pontlista;
typedef struct pont{int x,y;}pont;
typedef struct world{int meretx,merety;}world;

#endif // ENUM_STRUCT_H_INCLUDED
