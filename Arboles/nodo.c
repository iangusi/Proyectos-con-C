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
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
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
    DesconectaDerecho(*n);
    DesconectaIzquierdo(*n);
    free(*n);
    return 0;
}
int ConectaDerecho(Nodo n,Nodo o){
    if(n == NULL)
        return 1;
    n->derecha = o;
    return 0;
}
int ConectaIzquierdo(Nodo n,Nodo o){
    if(n == NULL)
        return 1;
    n->izquierda = o;
    return 0;
}
int ConsultaDerecho(Nodo n,Nodo *o){
    if(n == NULL)
        return 1;
    *o = n->derecha;
    return 0;
}
int ConsultaIzquierdo(Nodo n,Nodo *o){
    if(n == NULL)
        return 1;
    *o = n->izquierda;
    return 0;
}
int DesconectaDerecho(Nodo n){
    if(n == NULL)
        return 1;
    n->derecha = NULL;
    return 0;
}
int DesconectaIzquierdo(Nodo n){
    if(n == NULL)
        return 1;
    n->izquierda = NULL;
    return 0;
}

#endif