#ifndef NODO_C
#define NODO_C

#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"
#include "elemento.h"

int CreaNodo(Nodo *n){
    Nodo nodo = (Nodo)malloc(sizeof(t_nodo));
    nodo->enlace = NULL;
    *n = nodo;
    if(nodo == NULL)
        return 1;
    return 0;
}
int EscribeNodoElemento(Nodo n,Elemento e){
    if(n == NULL)
        return 1;
    n->elem = e;
    return 0;
}
int ObtieneNodoElemento(Nodo n,Elemento *e){
    if(n == NULL)
        return 1;
    *e = n->elem;
    return 0;
}
int DestruyeNodo(Nodo *n){
    if(*n == NULL)
        return 1;
    DesconectaEnlace(*n);
    free(*n);
    return 0;
}

int ConectaEnlace(Nodo n,Nodo o){
    if(n == NULL)
        return 1;
    n->enlace = o;
    return 0;
}
int ConsultaEnlace(Nodo n,Nodo *o){
    if(n == NULL)
        return 1;
    *o = n->enlace;
    return 0;
}
int DesconectaEnlace(Nodo n){
    if(n == NULL)
        return 1;
    n->enlace = NULL;
    return 0;
}

#endif