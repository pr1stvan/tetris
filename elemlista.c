#include "header.h"

/*Kit�rli a list�rol a kiv�nt elemet majd visszat�r az els� elem c�m�vel*/
elem *torol(elem*t)
{
    elem*tmp;


    if(t->elozo==NULL && t->kovetkezo==NULL)
    {
        free(t);
        return NULL;
    }
    else if(t->elozo==NULL)
    {
        tmp=t->kovetkezo;
        t->kovetkezo->elozo=NULL;
        free(t);
        return tmp;
    }
    else if(t->kovetkezo==NULL)
    {

        tmp=t->elozo;
        t->elozo->kovetkezo=NULL;
        free(t);
        while(tmp->elozo!=NULL)
        tmp=tmp->elozo;
        return tmp;
    }
    else
    {
        tmp=t->elozo;
        t->kovetkezo->elozo=t->elozo;;
        t->elozo->kovetkezo=t->kovetkezo;
        free(t);
        while(tmp->elozo!=NULL)
        tmp=tmp->elozo;
        return tmp;
    }
}
void lista_felszabadit(elem *lista)
{
    elem *iter,*tmp;
    if(lista==NULL)return;

    iter=lista;
    while(iter!=NULL)
    {
        tmp=iter->kovetkezo;
        free(iter);
        iter=tmp;
    }
}

/*A visszat�r�si �rt�k egy pointer a besz�rt elemre, mely egyben a lista eleje is*/
elem *beszur(elem*lista_eleje)
{
    elem*e;

    e=(elem*)malloc(sizeof(elem));

    e->iranyithato=1;
    e->elozo=NULL;
    e->kovetkezo=lista_eleje;

    if(lista_eleje!=NULL)e->kovetkezo->elozo=e;
    return e;
}
/*Kit�r�l egy eg�sz sort a j�t�kvil�gb�l, majd  visszat�r a lista elej�vel*/
elem* sortorol(elem *lista_eleje,int y)
{

    elem *e;
    elem*tmp;

    e=lista_eleje;
    while(e!=NULL)
    {
        tmp=e->kovetkezo;
        if(e->y==y)lista_eleje=torol(e);
        else if(e->y<y)e->y+=1;
        e=tmp;
    }
return lista_eleje;
}




elem *object_beszur(elem *lista,int tipus)
{

    int i;
    int r=rand()%3;
    int szin1,szin2,szin3;
    elem *iter;

    /*v�letlen sz�n*/
    switch(r)
    {
        case 0:
        szin1=255;
        szin2=0;
        szin3=0;
        break;
        case 1:
        szin1=0;
        szin2=255;
        szin3=0;
        break;
        case 2:
        szin1=0;
        szin2=0;
        szin3=255;
        break;
    }
    if(vilag.meretx>=2)
    {
        int kx=rand()%(vilag.meretx-1);
        switch(tipus)
        {
            case 0:
            lista=beszur(lista);
            lista->y=-2;
            lista->x=kx;
            for(i=-2;i<=0;i++)
            {
                lista=beszur(lista);
                lista->x=kx+1;
                lista->y=i;
            }
            break;
            case 1:
            lista=beszur(lista);
            lista->x=kx;
            lista->y=0;
            lista=beszur(lista);
            lista->x=kx;
            lista->y=-1;
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=-1;
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=-2;
            break;
            case 2:
            for(i=-2;i<=0;i++)
            {
                lista=beszur(lista);
                lista->y=i;
                lista->x=kx;
            }
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=-2;
            break;
            case 3:
            lista=beszur(lista);
            lista->x=kx;
            lista->y=-2;
            lista=beszur(lista);
            lista->x=kx;
            lista->y=-1;
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=-1;
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=0;
            break;
            case 4:
            for(i=-2;i<=0;i++)
            {
                lista=beszur(lista);
                lista->x=kx;
                lista->y=i;
            }
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=-1;
            break;
            case 5:
            lista=beszur(lista);
            lista->y=-1;
            lista->x=kx;
            lista=beszur(lista);
            lista->y=0;
            lista->x=kx;
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=-1;
            lista=beszur(lista);
            lista->x=kx+1;
            lista->y=0;
            break;
            case 6:
            for(i=-3;i<=0;i++)
            {
            lista=beszur(lista);
            lista->y=i;
            lista->x=kx;
            }
            break;
        }
    }
    else
    {
        for(i=-3;i<=0;i++)
        {
            lista=beszur(lista);
            lista->y=i;
            lista->x=0;
        }
    }
    /*V�letlen sz�n*/
    iter=lista;
    for(i=1;i<=4;i++)
    {
        iter->szin1=szin1;
        iter->szin2=szin2;
        iter->szin3=szin3;
        iter=iter->kovetkezo;
    }
    /*v�letlenszer� forgat�s*/
    for(i=0;i<=rand()%4;i++)
    {
        forgat(lista);
    }

    return lista;

}
