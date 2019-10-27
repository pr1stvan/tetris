#include "header.h"


/*pontlista kezelo fuggvenyek*/
int pont_beolvas(FILE *f,char *nev,int *p)
{
    char s[50];
    int c,i;

    c=fgetc(f);
    if(c==EOF || c=='\n')return 0;

    for(i=0;c!=EOF && c!='\n' && i<=48;i++)
    {
        s[i]=c;
        c=fgetc(f);
    }s[i]='\0';

    for(i=i-1;i>=0 && (s[i]>'9' || s[i]<'0');i--);
    while(i>=0 && s[i]!=' ')i--;

    sscanf(s+i,"%d",p);
    s[i]=0;
    strcpy(nev,s);
    return 1;

}


pontlista *pontlista_init(pontlista *lis)
{
    FILE *f;

    pontlista *uj;
    char s[50];
    int psz;

    f=fopen("high_score.txt","rt");

    lis=NULL;
    while(pont_beolvas(f,s,&psz)==1)
    {

        uj=(pontlista*)malloc(sizeof(pontlista));
        uj->nev=(char*)malloc(sizeof(char)*strlen(s)+1);
        strcpy(uj->nev,s);

        uj->psz=psz;

        uj->kov=lis;
        lis=uj;
    }

    fclose(f);
    return lis;
}


void pontlista_felszab(pontlista *lis)
{

     pontlista*tmp;
    while(lis!=NULL)
    {
        tmp=lis->kov;
        free(lis->nev);
        free(lis);
        lis=tmp;
    }
}
