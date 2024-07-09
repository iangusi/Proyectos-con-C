#ifndef NODO_H
#define NODO_H

#include "elemento.h"

typedef struct nodo{
    struct nodo *enlace;
    Elemento elem;
}t_nodo,*Nodo;

int CreaNodo(Nodo*);
int EscribeNodoElemento(Nodo,Elemento);
int ObtieneNodoElemento(Nodo,Elemento*);
int DestruyeNodo(Nodo*);

int ConectaEnlace(Nodo,Nodo);
int ConsultaEnlace(Nodo,Nodo*);
int DesconectaEnlace(Nodo);

#endif