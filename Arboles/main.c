#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "elemento.h"

int main(){
    Arbol a;
    Elemento e;
    int bandera;
    //Se crea el arbol
    bandera = CreaArbol(&a);
    if(bandera == 1)return 1;
    
    int nums[] = {2,4,6,8,9,5,3,2,1,12,45,67,87,43,32,65,76,66};
    //Llenamos el arbol con los numeros aleatorios
    for(int i=0;i<18;i++){
        //El elemento solo es un entero
        bandera = CreaElemento(&e);
        if(bandera == 1)return 1;
        EscribeElemento(e,nums[i]);
        //Aqui se inserta el elemento en el arbol
        bandera = InsertaNodoElemento(a,e);
        if(bandera == 1)return 1;
    }
    printf("Cantidad de nodos:%d\n",a->cantidad);
    Imprime(a,0);
    
    /*Pruebas de busqueda*/
    BuscarNodoElemento(a,12);
    BuscarNodoElemento(a,11);
    
    /*Pruebas para confirmar una eliminación correcta*/
    QuitaNodoElemento(a,4);
    printf("Cantidad de nodos:%d\n",a->cantidad);
    Imprime(a,0); //Imprimimos en inorden, osea de menor a mayor
    QuitaNodoElemento(a,2);
    printf("Cantidad de nodos:%d\n",a->cantidad);
    Imprime(a,1); //Imprimimos de mayor a menor
    QuitaNodoElemento(a,9);
    printf("Cantidad de nodos:%d\n",a->cantidad);
    Imprime(a,2); //Imprimimos en preorden
    QuitaNodoElemento(a,11);
    printf("Cantidad de nodos:%d\n",a->cantidad);
    Imprime(a,3); //Imprimimos en postorden
    
    /*
    //Destruimos todos los elementos del arbol
    Destruye(a,&a->raiz);
    printf("Cantidad de nodos:%d\n",a->cantidad);
    Imprime(a,0);
    */
    
    //Destruimos el arbol
    return DestruyeArbol(&a);
}