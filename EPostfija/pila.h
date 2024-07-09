#ifndef PILA_H
#define PILA_H

#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"
#include "elemento.h"

typedef struct pila{
    Nodo primero;
    int longitud;
}t_pila,*Pila;

int CreaPila(Pila*);
int InsertaNodoElemento(Pila,Elemento);
int QuitaNodoElemento(Pila,Elemento*);
int ConsultaPrimero(Pila,Elemento*);
int DestruyePila(Pila*);
int ImprimePila(Pila);

#endif