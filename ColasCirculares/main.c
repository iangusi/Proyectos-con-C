#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "elemento.h"

int main(){
    Cola c;
    Elemento e;
    
    int bandera;
    
    bandera = CreaCola(&c);
    if(bandera == 1) return 1;
    for(int i=0;i<10;i++){
        bandera = CreaElemento(&e);
        if(bandera == 1) return 1;
        bandera = EscribeElemento(e/*Elemento*/,200-(i*15)/*Ciclos*/,15-i/*Prioridad*/);
        if(bandera == 1) return 1;
        bandera = InsertaNodoElemento(c,e);
        if(bandera == 1) return 1;
        ImprimeCola(c);
    }
    printf("\nPlanificador: \n");
    Planificador(c);
    printf("\n");
    for(int i=0;i<10;i++){
        bandera = QuitaNodoElemento(c,&e);
        if(bandera == 1) return 1;
        bandera = DestruyeElemento(&e);
        if(bandera == 1) return 1;
        ImprimeCola(c);
    }
    
    return DestruyeCola(&c);
}
