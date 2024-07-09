#include <stdio.h>
#include <stdlib.h>

int creaMatriz(int***,int);
int borrarMatriz(int***,int);
int imprimir_llenar_Matriz(int***,int,char);
int determinanteMatriz(int***,int);

int main(){
    
    int **matriz=NULL, row=0;
    
    printf("Cantidad de filas y columnas: ");
    scanf("%d",&row);
    
    int c,l,d,b;
    c = creaMatriz(&matriz,row);
    if(c!=0)
        return -1;
    
    l = imprimir_llenar_Matriz(&matriz,row,'l');
    if(c!=0)
        return -1;
    
    d = determinanteMatriz(&matriz,row);
    
    b = borrarMatriz(&matriz,row);
    if(c!=0)
        return -1;
    
    printf("\n");
    printf("\ndeterminanteMatriz: %d",d);
    printf("\nFin de Programa");
    
    return 0;
}

int creaMatriz(int ***mat, int row){
    int **matrix = NULL;
    matrix = (int**)malloc(row*sizeof(int*));
    if(matrix==NULL)
        return -1;
    for(int i=0; i<row; i++){
        matrix[i] = (int*)malloc(row*sizeof(int));
        if(matrix[i]==NULL){
            for(--i; i>=0; i--)
                free(matrix[i]);
            free(matrix);
            matrix = NULL;
            return -1;
        }
        for(int j=0; j<row; j++)
            matrix[i][j] = 0;
    }
    *mat = matrix;
    return 0;
}

int borrarMatriz(int ***mat, int row){
    int **matrix = *mat;
    if(matrix==NULL)
        return -1;
    for(int i=0; i<row; i++)
        free(matrix[i]);
    free(matrix);
    *mat = NULL;
    return 0;
}

int imprimir_llenar_Matriz(int ***mat, int row, char accion){
    int **matrix = *mat;
    if(matrix==NULL)
        return -1;
    printf("\n");
    for(int i=0; i<row; i++){
        printf("\n");
        for(int j=0; j<row; j++){
            if(accion=='i')
                printf("%d\t",matrix[i][j]);
            else
                if(accion=='l'){
                    printf("matrix[%d][%d]: ",i,j);
                    scanf("%d",&matrix[i][j]);
                }else{
                    matrix[i][j]=(i+1)*(j+1);
                    printf("%d\t",matrix[i][j]);
                }
        }
    }
    return 0;
}

int determinanteMatriz(int ***mat, int row){
    int **matrix = *mat;
    
    if(matrix==NULL){
        printf("\nSe presento un error.");
        return 0;
    }
    
    imprimir_llenar_Matriz(&matrix,row,'i');
    
    if(row==2)
        return ((matrix[0][0])*(matrix[1][1]))-((matrix[0][1])*(matrix[1][0]));
    
    int deter=0,**m=NULL, y;
    for(int pivote=0; pivote<row; pivote++){
        if(creaMatriz(&m,row-1)==0){
            for(int i=1;i<row;i++){
                y=0;
                for(int j=0;j<row;j++){
                    if(j!=pivote){
                        m[i-1][y] = matrix[i][j];
                        y++;
                    }
                }
            }
            int signo=1;
            if(pivote%2!=0)
                signo=-1;
            deter += signo*(matrix[0][pivote])*determinanteMatriz(&m,row-1);
            borrarMatriz(&m,row-1);
        }else{
            printf("\nSe presento un error.");
            return 0;
        }
    }
    return deter;
}



