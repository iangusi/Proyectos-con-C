#ifndef ELEMENTO_H
#define ELEMENTO_H

typedef struct elemento{
    char *parte;
    int jerarquia;
}t_elemento,*Elemento;

int CreaElemento(Elemento*);
int EscribeElemento(Elemento,char*,int);
int ObtieneElemento(Elemento,char**,int*);
int DestruyeElemento(Elemento*);

#endif