#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "elemento.h"

int main(){
    Lista l;
    Elemento e;
    
    int bandera;
    
    CreaLista(&l);
    for(int i=0;i<10;i++){
        CreaElemento(&e);
        EscribeElemento(e,i+20);
        InsertaNodoElemento(l,e,0);
        ImprimeLista(l);
    }
    
    MergeSort(l,0,l->longitud-1);
    
    /*
    for(int i=0;i<10;i++){
        bandera = QuitaNodoElemento(l,&e,i);
        if(bandera == 1)break;
        DestruyeElemento(&e);
        ImprimeLista(l);
    }
    */
    
    return DestruyeLista(&l);
}
