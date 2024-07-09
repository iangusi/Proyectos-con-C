#ifndef COLA_C
#define COLA_C

#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "nodo.h"
#include "elemento.h"

int CreaCola(Cola *c){
    Cola cola = (Cola)malloc(sizeof(t_cola));
    if(cola == NULL)
        return 1;
    cola->primero = NULL;
    cola->ultimo = NULL;
    cola->longitud = 0;
    *c = cola;
    return 0;
}
int InsertaNodoElemento(Cola c,Elemento e){
    if(c == NULL)
        return 1;
    
    Nodo n;
    int bandera = CreaNodo(&n);
    if(bandera == 1)
        return 1;
    
    bandera = EscribeNodoElemento(n,e);
    if(bandera == 1)
        return 1;
    
    if(c->longitud == 0){
        c->primero = n;
        c->ultimo = n;
        ConectaEnlace(c->primero,c->ultimo);
        ConectaEnlace(c->ultimo,c->primero);
    }else
        InsertaNodo(c,n,c->primero,0);
    
    (c->longitud)++;
}
Nodo InsertaNodo(Cola c,Nodo n,Nodo o,int i){
    if(i==c->longitud){
        ConectaEnlace(n,o);
        c->ultimo = n;
        return n;
    }
    
    Elemento e1, e2;
    int v1, p1, v2, p2;
    ObtieneNodoElemento(n,&e1);
    ObtieneElemento(e1,&v1,&p1);
    ObtieneNodoElemento(o,&e2);
    ObtieneElemento(e2,&v2,&p2);
    
    if(p2 <= p1){
        ConectaEnlace(n,o);
        if(o == c->primero)
            c->primero = n;
        return n;
    }
    
    Nodo siguiente;
    ConsultaEnlace(o,&siguiente);
    ConectaEnlace(o,InsertaNodo(c,n,siguiente,i+1));
    return o;
}
int QuitaNodoElemento(Cola c,Elemento *e){
    int bandera = ConsultaPrimero(c,e);
    if(bandera == 1)
        return 1;
    
    Nodo siguiente;
    bandera = ConsultaEnlace(c->primero,&siguiente);
    if(bandera == 1)
        return 1;
    
    DestruyeNodo(&c->primero);
    
    bandera = ConectaEnlace(c->ultimo,siguiente);
    if(bandera == 1)
        return 1;
    c->primero = siguiente;
    (c->longitud)--;
    return 0;
}
int ConsultaPrimero(Cola c,Elemento *e){
    if(c == NULL || c->longitud == 0)
        return 1;
    return ObtieneNodoElemento(c->primero,e);
}
int ConsultaUltimo(Cola c,Elemento *e){
    if(c == NULL || c->longitud == 0)
        return 1;
    return ObtieneNodoElemento(c->ultimo,e);
}
int DestruyeCola(Cola *cola){
    if(*cola == NULL)
        return 1;
    Cola c = *cola;
    while(c->longitud != 0){
        Elemento e;
        QuitaNodoElemento(c,&e);
        DestruyeElemento(&e);
    }
    free(*cola);
    return 0;
}
int ImprimeCola(Cola c){
    if(c == NULL || c->longitud == 0)
        return 1;
    
    Nodo siguiente = c->primero;
    Elemento e;
    int bandera, v, p;
    printf("<");
    for(int i=0; i<c->longitud; i++){
        bandera = ObtieneNodoElemento(siguiente,&e);
        if(bandera == 1)
            return 1;
        bandera = ObtieneElemento(e,&v,&p);
        if(bandera == 1)
            return 1;
        printf("[%d,%d]",v,p);
        ConsultaEnlace(siguiente,&siguiente);
    }
    printf(">\n");
    return 0;
}
int Planificador(Cola c){
    if(c == NULL || c->longitud == 0)
        return 1;
    
    int ciclosXvuelta = 500;
    
    Nodo siguiente = c->primero;
    Nodo siguiente2 = c->primero;
    Elemento e;
    int bandera, v, p;
    
    int ciclosXprioridad;
    
    for(int i=0;;i=(i+1)%10){
        int prioridades = 0;
        for(int i=0; i<c->longitud; i++){
            bandera = ObtieneNodoElemento(siguiente,&e);
            if(bandera == 1)
                return 1;
            bandera = ObtieneElemento(e,&v,&p);
            if(bandera == 1)
                return 1;
            prioridades += p;
            ConsultaEnlace(siguiente,&siguiente);
        }
        if(prioridades == 0) return 0;
        
        ciclosXprioridad = ciclosXvuelta/prioridades;
        
        bandera = ObtieneNodoElemento(siguiente2,&e);
        if(bandera == 1)
            return 1;
        bandera = ObtieneElemento(e,&v,&p);
        if(bandera == 1)
            return 1;
        if(p != 0){
            int ciclos = ciclosXprioridad*p;
            if(v < ciclos){
                printf("actividad[%d]-ciclos:%d ",i,v);
                EscribeElemento(e,0,0);
            }
            else{  
                printf("actividad[%d]-ciclos:%d ",i,ciclos);
                EscribeElemento(e,v-ciclos,p);
            }
        }
        ImprimeCola(c);
        ConsultaEnlace(siguiente2,&siguiente2);
    }
}

#endif