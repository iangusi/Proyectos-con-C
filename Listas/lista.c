#ifndef LISTA_C
#define LISTA_C

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "nodo.h"
#include "elemento.h"

int CreaLista(Lista *l){
    Lista lista = (Lista)malloc(sizeof(t_lista));
    if(lista == NULL)
        return 1;
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->longitud = 0;
    *l = lista;
    return 0;
}
int InsertaNodoElemento(Lista l,Elemento e,int pos){
    if(l == NULL)
        return 1;
    if(pos > l->longitud || pos < 0)
        return 1;
        
    Nodo n;
    int bandera = CreaNodo(&n);
    if(bandera == 1)return 1;
    
    bandera = EscribeNodoElemento(n,e);
    if(bandera == 1)return 1;
    
    if(l->longitud == 0){
        l->primero = n;
        l->ultimo = n;
    }else if(pos == 0){
        bandera = ConectaSiguiente(n,l->primero);
        if(bandera == 1)return 1;
        bandera = ConectaAnterior(l->primero,n);
        if(bandera == 1)return 1;
        l->primero = n;
    } else if(pos == l->longitud){
        bandera = ConectaSiguiente(l->ultimo,n);
        if(bandera == 1)return 1;
        bandera = ConectaAnterior(n,l->ultimo);
        if(bandera == 1)return 1;
        l->ultimo = n;
    } else{
        Nodo actual = l->primero, pasado;
        for(int i=0;;i++){
            if(i == pos){
                ConsultaAnterior(actual,&pasado);
                ConectaSiguiente(pasado,n);
                ConectaSiguiente(n,actual);
                ConectaAnterior(actual,n);
                ConectaAnterior(n,pasado);
                break;
            }
            ConsultaSiguiente(actual,&actual);
        }
    }
    (l->longitud)++;
    return 0;
}
int QuitaNodoElemento(Lista l,Elemento *e,int pos){
    if(l == NULL)
        return 1;
    if(pos >= l->longitud || pos < 0)
        return 1;
    
    if(l->longitud == 1){
        ObtieneNodoElemento(l->primero,e);
        DestruyeNodo(&l->primero);
        l->primero = NULL;
        l->ultimo = NULL;
    }else if(pos == 0){
        ObtieneNodoElemento(l->primero,e);
        Nodo proximo;
        ConsultaSiguiente(l->primero,&proximo);
        DestruyeNodo(&l->primero);
        DesconectaAnterior(proximo);
        l->primero = proximo;
    }else if(pos == l->longitud-1){
        ObtieneNodoElemento(l->ultimo,e);
        Nodo pasado;
        ConsultaAnterior(l->ultimo,&pasado);
        DestruyeNodo(&l->ultimo);
        DesconectaSiguiente(pasado);
        l->ultimo = pasado;
    }else{
        Nodo actual = l->primero, pasado, proximo;
        for(int i=0;;i++){
            if(i == pos){
                ObtieneNodoElemento(actual,e);
                ConsultaAnterior(actual,&pasado);
                ConsultaSiguiente(actual,&proximo);
                DestruyeNodo(&actual);
                ConectaSiguiente(pasado,proximo);
                ConectaAnterior(proximo,pasado);
                break;
            }
            ConsultaSiguiente(actual,&actual);
        }
    }
    
    (l->longitud)--;
    return 0;
}
int ConsultaPrimero(Lista l,Elemento *e){
    if(l == NULL || l->longitud == 0)
        return 1;
    return ObtieneNodoElemento(l->primero,e);
}
int ConsultaUltimo(Lista l,Elemento *e){
    if(l == NULL || l->longitud == 0)
        return 1;
    return ObtieneNodoElemento(l->ultimo,e);
}
int DestruyeLista(Lista *lista){
    if(*lista == NULL)
        return 1;
    Lista l = *lista;
    int bandera;
    while(l->longitud != 0){
        Elemento e;
        bandera = QuitaNodoElemento(l,&e,0);
        if(bandera == 1) break;
        DestruyeElemento(&e);
    }
    free(*lista);
    return 0;
}
int ImprimeLista(Lista l){
    if(l == NULL || l->longitud == 0)
        return 1;
    
    Nodo siguiente = l->primero;
    Elemento e;
    int bandera, v;
    printf("<");
    while(siguiente != NULL){
        bandera = ObtieneNodoElemento(siguiente,&e);
        if(bandera == 1)
            return 1;
        bandera = ObtieneElemento(e,&v);
        if(bandera == 1)
            return 1;
        printf("[%d]",v);
        ConsultaSiguiente(siguiente,&siguiente);
    }
    printf(">\n");
    return 0;
}

void MergeSort(Lista l,int inicio, int fin){
    int largo = fin - inicio;
    if(largo < 1)return;
    int mitad = largo/2;
    
    int total = largo+1;
    int posPrimero = inicio;
    int totalPrimero = mitad+1;
    int posSegundo = inicio+mitad+1;
    int totalSegundo = largo-mitad;
    
    MergeSort(l,inicio,inicio+mitad);
    MergeSort(l,posSegundo,fin);
    
    Nodo segundo=l->primero, primero;
    for(int i=0;;i++){
        if(i==inicio)primero = segundo;
        if(i==posSegundo)break;
        ConsultaSiguiente(segundo,&segundo);
    }
    /*
    printf("inicio:%d, li:%d, segundo:%d, fin:%d\n",inicio,inicio+mitad,posSegundo,fin);
    printf("total:%d, totalPrimero:%d, totalSegundo:%d\n",total,totalPrimero,totalSegundo);
    */
    Elemento e1, e2;
    int val1, val2;
    for(int i=0;; i++){
        ObtieneNodoElemento(primero,&e1);
        ObtieneNodoElemento(segundo,&e2);
        ObtieneElemento(e1,&val1);
        ObtieneElemento(e2,&val2);
        if(val2 < val1){
            ConsultaSiguiente(segundo,&segundo);
            QuitaNodoElemento(l,&e2,posSegundo);
            InsertaNodoElemento(l,e2,posPrimero);
            totalSegundo--;
            posSegundo++;
        }else{
            totalPrimero--;
            ConsultaSiguiente(primero,&primero);
        }
        posPrimero++;
        if(totalPrimero==0)break;
        if(totalSegundo==0)break;
    }
    
    ImprimeLista(l);
}

#endif