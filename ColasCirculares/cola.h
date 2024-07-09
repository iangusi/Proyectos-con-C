#ifndef COLA_H
#define COLA_H

#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"
#include "elemento.h"

typedef struct cola{
    Nodo primero;
    Nodo ultimo;
    int longitud;
}t_cola,*Cola;

int CreaCola(Cola*);
int InsertaNodoElemento(Cola,Elemento);
Nodo InsertaNodo(Cola,Nodo,Nodo,int);
int QuitaNodoElemento(Cola,Elemento*);
int ConsultaPrimero(Cola,Elemento*);
int ConsultaUltimo(Cola,Elemento*);
int DestruyeCola(Cola*);
int ImprimeCola(Cola);
int Planificador(Cola);

#endif