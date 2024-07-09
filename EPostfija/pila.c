#ifndef PILA_C
#define PILA_C

#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "nodo.h"
#include "elemento.h"

int CreaPila(Pila *p){
    Pila pila = (Pila)malloc(sizeof(t_pila));
    if(pila == NULL) return 1;
    pila->primero = NULL;
    pila->longitud = 0;
    *p = pila;
    return 0;
}
int InsertaNodoElemento(Pila p,Elemento e){
    if(p == NULL) return 1;
    
    Nodo n;
    int bandera = CreaNodo(&n);
    if(bandera == 1) return 1;
    
    bandera = EscribeNodoElemento(n,e);
    if(bandera == 1) return 1;
    
    if(p->longitud > 0){
        bandera = ConectaEnlace(n,p->primero);
        if(bandera == 1) return 1;
    }
    p->primero = n;
    (p->longitud)++;
}
int QuitaNodoElemento(Pila p,Elemento *e){
    int bandera = ConsultaPrimero(p,e);
    if(bandera == 1) return 1;
    
    Nodo siguiente;
    bandera = ConsultaEnlace(p->primero,&siguiente);
    if(bandera == 1) return 1;
    
    DestruyeNodo(&p->primero);
    
    p->primero = siguiente;
    (p->longitud)--;
    return 0;
}
int ConsultaPrimero(Pila p,Elemento *e){
    if(p == NULL || p->longitud == 0) return 1;
    return ObtieneNodoElemento(p->primero,e);
}
int DestruyePila(Pila *pila){
    if(*pila == NULL) return 1;
    Pila p = *pila;
    while(p->longitud != 0){
        Elemento e;
        QuitaNodoElemento(p,&e);
        DestruyeElemento(&e);
    }
    free(*pila);
    return 0;
}
int ImprimePila(Pila p){
    if(p == NULL || p->longitud == 0) return 1;
    
    Nodo siguiente = p->primero;
    Elemento e;
    int bandera, j;
    char *parte;
    for(;;){
        bandera = ObtieneNodoElemento(siguiente,&e);
        if(bandera == 1)
            return 1;
        bandera = ObtieneElemento(e,&parte,&j);
        if(bandera == 1)
            return 1;
        printf("%s",parte);
        ConsultaEnlace(siguiente,&siguiente);
        if(siguiente==NULL)break;
    }
    printf("\n");
    return 0;
}

#endif