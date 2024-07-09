#ifndef ELEMENTO_C
#define ELEMENTO_C

#include <stdio.h>
#include <stdlib.h>
#include "elemento.h"

int CreaElemento(Elemento *e){
    Elemento elem = (Elemento)malloc(sizeof(t_elemento));
    *e = elem;
    if(elem == NULL)
        return 1;
    return 0;
}
int EscribeElemento(Elemento e,int c,int p){
    if(e == NULL)
        return 1;
    e->ciclos = c;
    e->prioridad = p;
    return 0;
}
int ObtieneElemento(Elemento e,int *c,int *p){
    if(e == NULL)
        return 1;
    *c = e->ciclos;
    *p = e->prioridad;
    return 0;
}
int DestruyeElemento(Elemento *e){
    if(*e == NULL)
        return 1;
    free(*e);
    return 0;
}

#endif