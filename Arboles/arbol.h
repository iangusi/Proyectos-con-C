#ifndef ARBOL_H
#define ARBOL_H

#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"
#include "elemento.h"

typedef struct arbol{
    Nodo raiz;
    int cantidad;
}t_arbol,*Arbol;

int CreaArbol(Arbol*);

int InsertaNodoElemento(Arbol,Elemento);
int InsertaNodo(Nodo*,Elemento);

int QuitaNodoElemento(Arbol,int);
int QuitaNodo(Nodo*,int);

Nodo Maximo(Nodo);
Nodo Minimo(Nodo);

int DestruyeArbol(Arbol*);
void Destruye(Arbol,Nodo*);

void Imprime(Arbol,int);
void ImprimeAscendente(Nodo);
void ImprimeDescendente(Nodo);
void ImprimePreorden(Nodo);
void ImprimePostorden(Nodo);

void BuscarNodoElemento(Arbol,int);
int Buscar(Nodo,int);

#endif