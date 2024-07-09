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
int EscribeElemento(Elemento e,int val){
    if(e == NULL)
        return 1;
    e->valor = val;
    return 0;
}
int ObtieneElemento(Elemento e,int *val){
    if(e == NULL)
        return 1;
    *val = e->valor;
    return 0;
}
int DestruyeElemento(Elemento *e){
    if(*e == NULL)
        return 1;
    free(*e);
    return 0;
}

#endif