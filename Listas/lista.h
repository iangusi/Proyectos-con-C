#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"
#include "elemento.h"

typedef struct lista{
    Nodo primero;
    Nodo ultimo;
    int longitud;
}t_lista,*Lista;

int CreaLista(Lista*);
int InsertaNodoElemento(Lista,Elemento,int);
int QuitaNodoElemento(Lista,Elemento*,int);
int ConsultaPrimero(Lista,Elemento*);
int ConsultaUltimo(Lista,Elemento*);
int DestruyeLista(Lista*);
int ImprimeLista(Lista);

void MergeSort(Lista,int,int);

#endif