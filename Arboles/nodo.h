#ifndef NODO_H
#define NODO_H

#include "elemento.h"

typedef struct nodo{
    Elemento elem;
    struct nodo *izquierda;
    struct nodo *derecha;
}t_nodo,*Nodo;

int CreaNodo(Nodo*);
int EscribeNodoElemento(Nodo,Elemento);
int ObtieneNodoElemento(Nodo,Elemento*);
int DestruyeNodo(Nodo*);

int ConectaIzquierdo(Nodo,Nodo);
int ConectaDerecho(Nodo,Nodo);
int ConsultaIzquierdo(Nodo,Nodo*);
int ConsultaDerecho(Nodo,Nodo*);
int DesconectaIzquierdo(Nodo);
int DesconectaDerecho(Nodo);

#endif