#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void LimpiarTableroInicial(short*,short,short);
void Reina(short*,short,short,short*);
void LimpiarTablero(short*,short,short,short);
void MarcarTablero(short*,short,short,short);
void ImprimirTablero(short*,short);

int main(){
    srand (time(NULL));
    
    short N=0, X=0, soluciones=0;
    printf("Problema de N Reinas\n");
    do{
        printf("Tamaño de tablero: ");
        scanf("%hd",&N);
        fflush(stdin);
    }while(N<1);
    do{
        printf("Casillas bloqueadas: ");
        scanf("%hd",&X);
        fflush(stdin);
    }while(X>N*N);
    
    short tablero[N][N];
    LimpiarTableroInicial(tablero[0],N,X);
    
    ImprimirTablero(tablero[0],N);
    
    Reina(tablero[0],N,0,&soluciones);
    
    printf("\nNumero de Soluciones: %d",soluciones);
    
    return 0;
}

void LimpiarTableroInicial(short *tablero,short n,short x){
    short i, *p = tablero, num;
    for(i=0;i<n*n;i++,p++)
        *p = 0;
    for(i=0;i<x;){
        num = rand()%(n*n);
        p = tablero+num;
        if(*p==0){
            *p = n+1;
            i++;
        }
    }
}

void ImprimirTablero(short *tablero,short n){
    for(int i=0;i<n*n;i++,tablero++){
        if(i%n==0)
            printf("\n");
        //printf("%d ",*tablero);
        if(*tablero==n+1)
            printf("X ");
        else if(*tablero>0)
            printf("Q ");
        else
            printf(". ");
    }
    printf("\n");
}

void LimpiarTablero(short *tablero, short pos,short n,short reina){
    for(;pos<n*n;pos++,tablero++)
        if(*tablero==-reina)
            *tablero = 0;
}

void MarcarTablero(short *pos,short n,short reina, short col){
    short *p = pos, fila = reina-1, c=col, i;
    /*** SUR ***/
    while(fila!=n-1){
        p += n;
        if(*p==0)
            *p = -reina;
        fila++;
    }
    
    p = pos, fila = reina-1, c=col;
    /*** SURESTE ***/
    while(fila!=n-1 && c!=n-1){
        p += n+1;
        if(*p==0)
            *p = -reina;
        fila++;
        c++;
    }
    
    p = pos, fila = reina-1, c=col;
    /*** SUROESTE ***/
    while(fila!=n-1 && c!=0){
        p += n-1;
        if(*p==0)
            *p = -reina;
        fila++;
        c--;
    }
}

void Reina(short *tablero,short n,short reinas,short *sol){
    if(reinas == n){
        (*sol)++;
        ImprimirTablero(tablero,n);
        printf("Solucion %d\n",*sol);
        return;
    }
    
    short i, *p = tablero+(n*reinas), reina = reinas+1;
    
    for(i=0;i<n;i++,p++){
        if(*p == 0){
            *p = reina;
            MarcarTablero(p,n,reina,i);
            //ImprimirTablero(tablero,n);
            Reina(tablero,n,reina,sol);
            LimpiarTablero(p,(i+(reinas*n)),n,reina);
            *p = 0;
        }
    }
}