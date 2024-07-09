#ifndef NODO_H
#define NODO_H

#include "elemento.h"

typedef struct nodo{
    Elemento elem;
    struct nodo *siguiente;
    struct nodo *anterior;
}t_nodo,*Nodo;

int CreaNodo(Nodo*);
int EscribeNodoElemento(Nodo,Elemento);
int ObtieneNodoElemento(Nodo,Elemento*);
int DestruyeNodo(Nodo*);

int ConectaSiguiente(Nodo,Nodo);
int ConectaAnterior(Nodo,Nodo);
int ConsultaSiguiente(Nodo,Nodo*);
int ConsultaAnterior(Nodo,Nodo*);
int DesconectaSiguiente(Nodo);
int DesconectaAnterior(Nodo);

#endif