#ifndef NODO_C
#define NODO_C

#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"
#include "elemento.h"

int CreaNodo(Nodo *n){
    Nodo nodo = (Nodo)malloc(sizeof(t_nodo));
    if(nodo == NULL)
        return 1;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    *n = nodo;
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
    DesconectaSiguiente(*n);
    DesconectaAnterior(*n);
    free(*n);
    return 0;
}
int ConectaSiguiente(Nodo n,Nodo o){
    if(n == NULL)
        return 1;
    n->siguiente = o;
    return 0;
}
int ConectaAnterior(Nodo n,Nodo o){
    if(n == NULL)
        return 1;
    n->anterior = o;
    return 0;
}
int ConsultaSiguiente(Nodo n,Nodo *o){
    if(n == NULL)
        return 1;
    *o = n->siguiente;
    return 0;
}
int ConsultaAnterior(Nodo n,Nodo *o){
    if(n == NULL)
        return 1;
    *o = n->anterior;
    return 0;
}
int DesconectaSiguiente(Nodo n){
    if(n == NULL)
        return 1;
    n->siguiente = NULL;
    return 0;
}
int DesconectaAnterior(Nodo n){
    if(n == NULL)
        return 1;
    n->anterior = NULL;
    return 0;
}

#endif