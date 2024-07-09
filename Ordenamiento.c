#include <stdio.h>
#include <stdlib.h>

short ajustarColeccion(short**,short);
void imprimir(short**,short);
short leerArchivo(short**,short*);
void copiarArreglo(short**,short,short**);
void ordenSeleccion(short**,short);
void ordenBurbuja(short**,short);
void ordenInsercion(short**,short);
void QuickSort(short*,short,short,short);
void MergeSort(short*,short,short,short);
void MergeSortI(short*,short);
    
int main()
{
    printf("-ORDENAMIENTO DE MAXIMO 3000 CARACTERES-\n");
    
    short *caracteres = NULL, tamanio = 0;
    short estadoDeArchivo = leerArchivo(&caracteres,&tamanio);
    
    //Nos aseguramos que el archivo se haya leido exitosamente
    if(estadoDeArchivo != 0)
        return -1;
    
    char opc;
    
    for(;;){
        printf("\n1- Ordenamiento Seleccion");
        printf("\n2- Ordenamiento Burbuja");
        printf("\n3- Ordenamiento Insercion");
        printf("\n4- Ordenamiento QuickSort");
        printf("\n5- Ordenamiento MergeSort Recursivo");
        printf("\n6- Ordenamiento MergeSort Iterativo");
        printf("\n0- Salir");
        printf("\nEscoja una opción: ");
        scanf("%c", &opc);
        fflush(stdin);
        
        printf("\n");
        
        if(opc=='1')
            ordenSeleccion(&caracteres,tamanio);
        else if(opc=='2')
            ordenBurbuja(&caracteres,tamanio);
        else if(opc=='3')
            ordenInsercion(&caracteres,tamanio);
        else if(opc=='4'){
            short *r=NULL;
            copiarArreglo(&caracteres,tamanio,&r);
            if(r!=NULL){
                QuickSort(r,0,tamanio-1,tamanio);
                imprimir(&r,tamanio);
                free(r);
            }
        }
        else if(opc=='5'){
            short *r=NULL;
            copiarArreglo(&caracteres,tamanio,&r);
            if(r!=NULL){
                MergeSort(r,0,tamanio-1,tamanio);
                imprimir(&r,tamanio);
                free(r);
            }
        }
        else if(opc=='6'){
            short *r=NULL;
            copiarArreglo(&caracteres,tamanio,&r);
            if(r!=NULL){
                MergeSortI(r,tamanio);
                free(r);
            }
        }
        else if(opc=='0'){
            free(caracteres);
            printf("\nFIN DEL PROGRAMA");
            return 0;
        }
        else printf("\nOpción invalida\n");
    }
    
}

short ajustarColeccion(short **caracteres, short tamanio){
    //Ajustamos el arreglo al nuevo tamaño
    *caracteres = (short*)realloc(*caracteres, tamanio*sizeof(short));
    //Devolvemos 0 de ok y 1 si ocurrio un error
    return *caracteres != NULL ? 0:1;
}

void imprimir(short **caracteres, short tamanio){
    int i;
    short *p = *caracteres;
    for(i=0;i<tamanio;i++,p++){
        //printf("[%d - %c]",*p,*p);
        printf("%c",*p);
    }
    printf("\n");
}

short leerArchivo(short **arr, short *tamanio){
    
    short size = 0;
    
    short *caracteres = (short*)malloc(3000*sizeof(short));
    
    char str[40];
    printf("\nNombre del txt: ");
    scanf("%s",str);
    fflush(stdin);
    
    //Abrimos el archivo
    FILE *f = fopen(str,"r");
    if(f==NULL){
        printf("\nError al abrir archivo");
        return -1;
    }
    //Mientras el archivo tenga contenido y no sobrepase los 3000 caracteres
    short *p = caracteres;
    while(!feof(f) && size<3000){
        //Obtenemos el caracter
        char caracter = fgetc(f);
        //Si no es un simbolo de enter o el final del archivo
        if(caracter != '\n' && (short)caracter != -1){
            //El tamaño aumenta
            size++;
            //Agregamos el caracter en ASCII
            *p = (int)caracter;
            p++;
        }
    }
    
    //Cerramos el archivo
    fclose(f);
    
    ajustarColeccion(&caracteres, size);
    
    //Asignamos el arreglo
    *arr = caracteres;
    //Asignamos el tamaño
    *tamanio = size;
    
    printf("Lectura exitosa del archivo\n");
    imprimir(arr,size);
    
    return 0;
}

void copiarArreglo(short **caracteres, short tamanio, short **nuevo){
    short *copia = (short*)malloc(tamanio*sizeof(short)), *c=copia, *p=*caracteres;
    if(copia == NULL)
        return;
    for(int i=0; i<tamanio; i++, p++, c++){
        *c = *p;
    }
    *nuevo = copia;
}

void ordenSeleccion(short **caracteres, short tamanio){
    short i,j,k,l, aux, *r=NULL;
    copiarArreglo(caracteres, tamanio, &r);
    if(r==NULL)
        return;
    short *r1 = r; 
    k=tamanio-1;
    for(i=0;i<k;i++,r1++){
        short *r2 = r1+1;
        l=i+1;
        for(j=l;j<tamanio;j++,r2++){
            if(*r1 > *r2){
                aux = *r1;
                *r1 = *r2;
                *r2 = aux;
            }
        }
    }
    imprimir(&r,tamanio);
    free(r);
}

void ordenBurbuja(short **caracteres, short tamanio){
    short i,j,k,l, aux, seguir, *r=NULL;
    k=tamanio-1;
    copiarArreglo(caracteres, tamanio, &r);
    if(r==NULL)
        return;
    for(i=0;i<k;i++){
        seguir = 0;
        short *r1 = r, *r2 = r1+1;
        l=k-i;
        for(j=0;j<l;j++,r1++,r2++){
            if(*r1 > *r2){
                aux = *r1;
                *r1 = *r2;
                *r2 = aux;
                seguir = 1;
            }
        }
        
        if(seguir==0)
            break;
    }
    imprimir(&r,tamanio);
    free(r);
}

void ordenInsercion(short **caracteres, short tamanio){
    short i, j, l=tamanio-1, *r=NULL, *r2, aux;
    copiarArreglo(caracteres, tamanio, &r);
    if(r==NULL)
        return;
    short *r1 = r+1;
    for(i=0;i<l;i++,r1++){
        r2 = r1-1;
        aux = *r1;
        for(j=i;j>=0 && aux<*r2;j--,r2--){
            *(r2+1) = *r2;
        }
        *(r2+1)=aux;
    }
    imprimir(&r,tamanio);
    free(r);
}


void QuickSort(short *caracteres, short inf, short sup, short size){
    if(inf >= sup){
        return;
    }
    short *k = caracteres+sup, *pinza = caracteres+inf;
    short aux, izquierda=inf, derecha=sup;
    while(izquierda < derecha){
        if(*pinza > *k){
            if(izquierda+1 < derecha){
                aux = *(k-1);
                *(k-1) = *k;
            }else
                aux = *k;
            
            *k = *pinza;
            *pinza = aux; 
            
            k--;
            derecha--;
        }else{
            pinza++;
            izquierda++;
        }
    }
    QuickSort(caracteres,inf,derecha-1,size);
    //printf("\nBloque(%hd - %hd) LI:%hd, LD:%hd\n",inf,sup,izquierda,derecha);
    //imprimir(&caracteres,size);
    QuickSort(caracteres,derecha+1,sup,size);
    //printf("\nBloque(%hd - %hd) LI:%hd, LD:%hd\n",inf,sup,izquierda,derecha);
    //imprimir(&caracteres,size);
}

void MergeSort(short *caracteres, short inf, short sup, short size){
    if(inf >= sup){
        return;
    }
    short mitad = (short) (inf + sup)/2;
    
    //printf("\n%d\n",mitad);
    
    MergeSort(caracteres,inf,mitad,size);
    MergeSort(caracteres,mitad+1,sup,size);
    
    //printf("\nBloque(%hd - %hd)\n",inf,sup);
    
    short totalElementos = sup+1-inf;
    
    short *arr = (short*)malloc(totalElementos*sizeof(short)), *p = arr;
    if(arr==NULL)
        return;
    
    short elementosIzquierda = mitad+1-inf, elementosDerecha = sup-mitad;
    short *ei = caracteres+inf;
    short *ed = caracteres+mitad+1;
    
    short i;
    for(i=0; i<totalElementos; i++,p++){
        if(( *ei < *ed && elementosIzquierda>0 ) || elementosDerecha==0){
            *p = *ei;
            elementosIzquierda--;
            ei++;
        }else{
            if(( *ei >= *ed && elementosDerecha>0 ) || elementosIzquierda==0){
                *p = *ed;
                elementosDerecha--;
                ed++;
            }
        }
    }
    
    short *r = caracteres+inf;
    p = arr;
    for(;totalElementos>0;totalElementos--,r++,p++){
        *r = *p;
    }
    
    //imprimir(&caracteres,size);
    free(arr);
}

void MergeSortI(short *caracteres,short size){
    
    short i, j, k, l, m, n, o;
    short L=2*size, corte=0, medio=0;
    short *r=NULL;
    copiarArreglo(&caracteres, size, &r);
    if(r==NULL)
        return;
    
    for(i=2, j=1; i<L; i*=2, j*=2){
        for(k=0; k<size; k+=i){
            corte=k+i;
            if(corte>size)
                corte=size;
            medio=k+j;
            if(medio>size)
                corte=size;
            
            l=k;
            m=medio;
            
            for(n=k; n<corte; n++){
                if(caracteres[l] < caracteres[m] && l<medio || m>=corte){
                    r[n]= caracteres[l];
                    l++;
                }else if(caracteres[l] >= caracteres[m] && m<corte || l>=medio){
                    r[n]= caracteres[m];
                    m++;
                }
            }
        }
        for(k=0; k<size; k++)
                caracteres[k] = r[k];
                
    }
    imprimir(&caracteres,size);
    free(r);
}