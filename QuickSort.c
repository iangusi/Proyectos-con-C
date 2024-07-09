#include <stdio.h>
#include <stdlib.h>

typedef struct limit{
    int inf;
    int sup;
} t_limit, *Limit;

void IQuickSort(int*,int);
void QuickSort(int*,int,int,int);
int Particion(int*,int,int);

int AmpliarArreglo(Limit*,int*);
int QuitarArreglo(Limit,int*);


int main(){
    int a[] = {1,4,5,87,6,4,3,2,5,7,9,6,11};
    int b[] = {1,4,5,87,6,4,3,2,5,7,9,6,11};
    printf("\n_______IQuickSort:\n");
    IQuickSort(a,13);
    printf("_______QuickSort:\n");
    QuickSort(b,0,12,13);
    return 0;
}

void IQuickSort(int *arr, int tamaño){
    int size = 0;
    Limit limites;
    AmpliarArreglo(&limites,&size);
    limites[0].inf = 0;
    limites[0].sup = tamaño-1;
    
    printf("Arreglo:");
    for(int i=0; i<tamaño; i++)
        printf(" %d ",arr[i]);
    printf("\nLimites: [0,%d]\n",tamaño-1);
    printf("size: %d\n\n",size);
        
    while(size!=0){
        int li = limites[0].inf;
        int ls = limites[0].sup;
        
        QuitarArreglo(limites,&size);
        
        int pivote = Particion(arr,li,ls);
        printf("Pivote: %d\n",pivote);
        
        if(pivote-li > 1){
            AmpliarArreglo(&limites,&size);
            limites[size-1].sup = pivote-1;
            limites[size-1].inf = li;
        }
        
        if(ls-pivote > 1){
            AmpliarArreglo(&limites,&size);
            limites[size-1].sup = ls;
            limites[size-1].inf = pivote+1;
        }
        
        printf("Arreglo:");
        for(int i=0; i<tamaño; i++)
            printf(" %d ",arr[i]);
        printf("\nLimites:");
        for(int i=0; i<size; i++)
            printf(" [%d,%d]",limites[i].inf,limites[i].sup);
        printf("\n");
        printf("size: %d\n\n",size);
    }
}
void QuickSort(int *arr, int inf, int sup, int size){
    if(inf >= sup){
        return;
    }
    int pivote = Particion(arr,inf,sup);
    printf("Pivote: %d\n",pivote);
    
    printf("Arreglo:");
    for(int i=0; i<size; i++)
        printf(" %d ",arr[i]);
    printf("\nLimites:");
    printf(" [%d,%d] ",inf,pivote-1);
    printf(" [%d,%d]\n\n",pivote+1,sup);
    
    QuickSort(arr,inf,pivote-1,size);
    QuickSort(arr,pivote+1,sup,size);
}
int Particion(int *arr, int inf, int sup){
    int *pivote = arr+sup, *k = arr+inf;
    int aux;
    while(inf < sup){
        if(*k > *pivote){
            if(inf+1 < sup){
                aux = *(pivote-1);
                *(pivote-1) = *pivote;
            }else
                aux = *pivote;
            
            *pivote = *k;
            *k = aux;
            
            pivote--;
            sup--;
        }else{
            k++;
            inf++;
        }
    }
    return sup;
}

int AmpliarArreglo(Limit *a, int *tamaño){
    (*tamaño)++;
    if(*tamaño == 1)
        *a = (Limit)malloc(sizeof(t_limit));
    else
        *a = (Limit)realloc(*a,(*tamaño)*sizeof(t_limit));
    if(*a == NULL)
        return 1;
    return 0;
}
int QuitarArreglo(Limit a, int *tamaño){
    (*tamaño)--;
    
    for(int i=0; i<(*tamaño); i++)
        a[i] = a[i+1];
    
    a = (Limit)realloc(a,(*tamaño)*sizeof(t_limit));
    
    if(a == NULL)
        return 1;
    return 0;
}




