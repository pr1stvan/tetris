#include "header.h"

/*Az iranyithato elemeket nem veszi figyelembe*/
int van_elem(elem *lista_eleje,int x,int y)
{
    elem*e;
    for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
    if((e->x==x && e->y==y)&& (e->iranyithato==0))return 1;
    return 0;
}

/*Ha nem szabad forgatni nem forgat*/
void forgat(elem *elemek)
{
    elem uj[4];
    int i;
    int minx,maxy,x,y;
    elem *iter;
    int szam;
    int meg_nem_lehet=0;
    int hatos_szamu_sor=0,hatos_szamu_oszlop=0;

   /*A négy elem meglétének ellenörzése*/
    szam=0;
    for(iter=elemek;iter!=NULL;iter=iter->kovetkezo)
    {
        if(iter->iranyithato)szam+=1;
        if(szam>=4)break;
    }
    if(szam<4)return;

   /*Egy tömb feltöltése az forgatandó(irányitható) elemekkel (elsõ négy)*/
    i=0;
    for(iter=elemek;iter!=NULL && i<=3;iter=iter->kovetkezo)
    {
        if(iter->iranyithato)
        {
            uj[i]=*iter;
            i++;
        }
    }
    /*Annak ellenörzése ,hogy hatos számú-e*/
    hatos_szamu_oszlop=1;
    hatos_szamu_sor=1;
    for(i=1;i<=3;i++)
    {
        if(uj[0].x!=uj[i].x)hatos_szamu_oszlop=0;
        if(uj[0].y!=uj[i].y)hatos_szamu_sor=0;
    }
    /*Ezután elõször megnézi, hogy hova kell tenni a transzformált alakot*/
    minx=uj[0].x;
    for(i=1;i<=3;i++)
        if(uj[i].x<minx)minx=uj[i].x;

    maxy=uj[0].y;
    for(i=1;i<=3;i++)
      if(uj[i].y>maxy)maxy=uj[i].y;

    /*Forgatás az origó körül*/
    for(i=0;i<=3;i++)
    {
        int tmp=uj[i].x;
        uj[i].x=-uj[i].y;
        uj[i].y=tmp;
    }

    /*Eltolás a megfelelõ helyre*/
    /*Az új legkisebb*/
    x=uj[0].x;
    for(i=1;i<=3;i++)
    {
        if(uj[i].x<x)x=uj[i].x;
    }
    /*Az új legnagyobb*/
    y=uj[0].y;
    for(i=1;i<=3;i++)
    {
        if(uj[i].y>y)y=uj[i].y;
    }
    /*ennyivel kell tolni*/
     x=minx-x;
    y=maxy-y;
    if(hatos_szamu_oszlop==1)
    {
        x-=2;
        y-=1;
    }
    else if(hatos_szamu_sor==1)
    {
        x+=2;
        y+=1;
    }

    /*A tényleges eltolás*/

    for(i=0;i<=3;i++)
    {
        uj[i].x+=x;
        uj[i].y+=y;
    }
    /*Meg kell nézni, hogy a transzformáció lehetséges-e ha nem hatos számú*/
    if(!hatos_szamu_oszlop && !hatos_szamu_sor)
    {
        for(i=0;i<=3;i++)
        {
            if((uj[i].x>vilag.meretx-1) || uj[i].y>vilag.merety-1)
            {
                meg_nem_lehet=1;
            }
            if(van_elem(elemek,uj[i].x,uj[i].y))return;
        }
        /*Ha a pálya jobb szélén van kísérlet a transzformációra balra tolással*/
        if(meg_nem_lehet)
        {
            for(i=0;i<=3;i++)
            {
                uj[i].x-=1;
                /*Itt ellenörzi azt is ,hogy nem került-e ki az elem balra.*/
                if(van_elem(elemek,uj[i].x,uj[i].y) || (uj[i].x>vilag.meretx-1) || uj[i].y>vilag.merety-1 || uj[i].x<0)return;
            }
        }
    }
    /*Ha hatos számú, máshogy kell megnézni*/
    else
    {
        for(i=0;i<=3;i++)
        {
            if((uj[i].x>vilag.meretx-1) || uj[i].y>vilag.merety-1 || uj[i].x<0 || van_elem(elemek,uj[i].x,uj[i].y))
            return;
        }
    }

    /*A régi elemek helyére az új transzformált elemek kerülnek*/
    i=0;
    for(iter=elemek;iter!=NULL && i<=3;iter=iter->kovetkezo)
    {
        if(iter->iranyithato)
        {
            *iter=uj[i];
            i++;
        }
    }
}
int sortelevan(elem *lista_eleje,int y)
{
    elem *e;
    int db=0;

    for(e=lista_eleje;e!=NULL;e=e->kovetkezo)
        if(e->y==y && e->iranyithato==0)db++;

    if(db>=vilag.meretx)return 1;
    return 0;
}
