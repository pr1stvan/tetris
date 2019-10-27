#ifndef EREDMENYLISTA_H_INCLUDED
#define EREDMENYLISTA_H_INCLUDED


void high_score();
void pontlista_felszab(pontlista *);

pontlista *pontlista_init(pontlista *);
int pont_beolvas(FILE *,char *,int *);

#endif // EREDMENYLISTA_H_INCLUDED
