#ifndef ARBOL_C
#define ARBOL_C

#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "nodo.h"
#include "elemento.h"

int CreaArbol(Arbol *a){
    //Apartamos espacio en memoria
    Arbol arbol = (Arbol)malloc(sizeof(t_arbol));
    //Si no se pudo, regresamos
    if(arbol == NULL)
        return 1;
    //Al inicio no hay raiz ni nodos
    arbol->raiz = NULL;
    arbol->cantidad = 0;
    //Le pasamos el arbol por referencia
    *a = arbol;
    return 0;
}
int InsertaNodoElemento(Arbol a,Elemento e){
    //Si no hay arbol, salimos
    if(a == NULL)
        return 1;
    //Si no se pudo insertar el nodo, salimos
    if(InsertaNodo(&a->raiz,e) == 1)
        return 1;
    //En caso contrario, aumentamos la cantidad de nodos
    (a->cantidad)++;
    return 0;
}
int InsertaNodo(Nodo *actual,Elemento e){
    Nodo central = *actual;
    //Si central esta vacio, esa es la posicion donde se debe insertar el nuevo elemento
    if(central == NULL){
        //Creamos el nodo en central
        int b = CreaNodo(&central);
        if(b==1) return 1;
        //Le asignamos el elemento
        EscribeNodoElemento(central,e);
        //Pasamos el nodo por referencia
        *actual = central;
        return 0;
    }
    /*
    En caso de que central sea un nodo, debemos evaluar si nuestro elemento
    se insertara a la izquierda o derecha de central.
    */
    Elemento elem;
    //Obtenemos el elemento de central
    ObtieneNodoElemento(central,&elem);
    int val, valCentral;
    //Obtenemos sus valores numericos
    ObtieneElemento(e,&val);
    ObtieneElemento(elem,&valCentral);
    //Si el nuevo elemento es menor al elemento de central, avanzamos por la izquierda
    if(val < valCentral)
        return InsertaNodo(&central->izquierda,e);
    //De lo contrario, si es mayor o igual, avanzamos por la derecha
    return InsertaNodo(&central->derecha,e);
}
int QuitaNodoElemento(Arbol a,int val){
    //Si no hay arbol, salimos
    if(a == NULL)
        return 1;
    //Si no existe el elemento a eliminar, salimos
    if(QuitaNodo(&a->raiz,val)==1)
        return 1;
    //En caso contrario, disminuimos la cantidad de nodos
    (a->cantidad)--;
    return 0;
}
int QuitaNodo(Nodo *actual,int val){
    Nodo central = *actual;
    /*
    Si llegamos al final del arbol, a un punto donde central esta vacio
    significa que el valor a eliminar no existe en el arbol, por lo tanto
    no queda mas que regresar
    */
    if(central == NULL)return 1;
    /*
    En cada nodo por el que pasemos, deberemos preguntar si es el nodo que
    buscamos o si debemos buscar a la derecha o izquierda
    */
    Elemento elem;
    ObtieneNodoElemento(central,&elem);
    int valCentral;
    ObtieneElemento(elem,&valCentral);
    //Si el valor a eliminar es menor, avanzamos a la izquierda
    if(val < valCentral)
        return QuitaNodo(&central->izquierda,val);
    //Si el valor a eliminar es mayor, avanzamos a la izquierda
    if(val > valCentral)
        return QuitaNodo(&central->derecha,val);
    
    /*
    Si ninguna de las dos condiciones pasadas se cumplio, entonces,
    central es el nodo a eliminar
    */
    //Si central tiene un nodo a la izquierda
    if(central->izquierda!=NULL){
        //Decimos que ese nodo ahora ocupara el lugar de central
        *actual = central->izquierda;
        //Buscamos el nodo más grande del lado izquierdo
        Nodo mayor = Maximo(central->izquierda);
        //Conectamos la parte derecha de central, con el lado derecho de mayor
        mayor->derecha = central->derecha;
    }
    /*
    Si no tenemos lado izquierdo que utilizar,
    entonces el nodo derecho ocupara el lugar de central
    */
    else 
        *actual = central->derecha;
    
    //Ahora solo queda eliminar central
    Elemento e;
    ObtieneNodoElemento(central,&e);
    DestruyeNodo(&central);
    printf("Valor [%d] eliminado!\n",e->valor);
    DestruyeElemento(&e);
    return 0;
}
Nodo Maximo(Nodo c){
    //Nos movemos a la derecha tanto como podamos
    while(c->derecha!=NULL)
        c = c->derecha;
    return c;
}
Nodo Minimo(Nodo c){
    //Nos movemos a la izquierda tanto como podamos
    while(c->izquierda!=NULL)
        c = c->izquierda;
    return c;
}
int DestruyeArbol(Arbol *a){
    //Si no hay arbol, salimos
    if(*a == NULL)
        return 1;
    //Destruimos todos los nodos que tenga
    Destruye(*a,&(*a)->raiz);
    //Comprobamos que el arbol ya no tenga ni raiz
    if((*a)->raiz != NULL) return 1;
    //Liberamos el espacio del arbol
    free(*a);
    return 0;
}
void Destruye(Arbol a,Nodo *central){
    //Si llegamos a las hojas, regresamos
    if(*central == NULL)
        return;
    //Primero destruimos las ramas
    Destruye(a,&(*central)->izquierda);
    Destruye(a,&(*central)->derecha);
    //Despues destruimos a central
    Elemento e;
    ObtieneNodoElemento(*central,&e);
    DestruyeNodo(central);
    DestruyeElemento(&e);
    *central = NULL;
    //La cantidad de nodos en el Arbol disminuye
    (a->cantidad)--;
    return;
}
void Imprime(Arbol a,int v){
    if(a==NULL)return;
    printf("[");
    if(v == 0) ImprimeAscendente(a->raiz);
    if(v == 1) ImprimeDescendente(a->raiz);
    if(v == 2) ImprimePreorden(a->raiz);
    if(v == 3) ImprimePostorden(a->raiz);
    printf("]\n");
}
void ImprimeAscendente(Nodo central){
    if(central == NULL) return;
    
    ImprimeAscendente(central->izquierda);
    
    Elemento e;
    ObtieneNodoElemento(central,&e);
    printf(" %d ",e->valor);
    
    ImprimeAscendente(central->derecha);
}
void ImprimeDescendente(Nodo central){
    if(central == NULL) return;
    
    ImprimeDescendente(central->derecha);
    
    Elemento e;
    ObtieneNodoElemento(central,&e);
    printf(" %d ",e->valor);
    
    ImprimeDescendente(central->izquierda);
}
void ImprimePreorden(Nodo central){
    if(central == NULL) return;

    Elemento e;
    ObtieneNodoElemento(central,&e);
    printf(" %d ",e->valor);
    
    ImprimePreorden(central->izquierda);
    ImprimePreorden(central->derecha);
}
void ImprimePostorden(Nodo central){
    if(central == NULL) return;
    
    ImprimePostorden(central->izquierda);
    ImprimePostorden(central->derecha);
    
    Elemento e;
    ObtieneNodoElemento(central,&e);
    printf(" %d ",e->valor);
}
void BuscarNodoElemento(Arbol a,int val){
    if(a==NULL)return;
    
    if(Buscar(a->raiz,val)==1)
        printf("No se encontro el valor [%d]\n",val);
    else
        printf("¡Valor [%d] encontrado!\n",val);
}
int Buscar(Nodo central,int val){
    /*
    Si llegamos al final del arbol, a un punto donde central esta vacio
    significa que el valor a buscar no existe en el arbol, por lo tanto
    no queda mas que regresar
    */
    if(central==NULL)return 1;
    //Obtenemos el valor en el nodo y comparamos
    Elemento e;
    ObtieneNodoElemento(central,&e);
    //Si el num que buscamos es menor, avanzamos por la izquierda
    if(val < e->valor) return Buscar(central->izquierda,val);
    //Si el num que buscamos es mayor, avanzamos por la derecha
    if(val > e->valor) return Buscar(central->derecha,val);
    //Si ninguna de las condiciones se cumplio, encontramos el elemento
    return 0;
}

#endif