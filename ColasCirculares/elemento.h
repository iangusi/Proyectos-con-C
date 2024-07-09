#ifndef ELEMENTO_H
#define ELEMENTO_H

typedef struct elemento{
    int ciclos;
    int prioridad;
}t_elemento,*Elemento;

int CreaElemento(Elemento*);
int EscribeElemento(Elemento,int,int);
int ObtieneElemento(Elemento,int*,int*);
int DestruyeElemento(Elemento*);

#endif