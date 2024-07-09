#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CreaTensor(int*******,int,int,int,int,int,int);
int ImprimeTensor(int*******,int,int,int,int,int,int);
int LiberaTensor(int*******,int,int,int,int,int);
int CambioDeVelocidad();

int main(){
    srand(time(NULL));
    
    int ******tensor = NULL;
    
    printf("Creacion de la matriz: %d\n",CreaTensor(&tensor,1,1,1,1,3,3));
    printf("Creacion de la matriz: %d\n",ImprimeTensor(&tensor,1,1,1,1,3,3));
    printf("Liberacion de la matriz: %d\n",LiberaTensor(&tensor,1,1,1,1,3));
    
    return 0;
}

int CreaTensor(int *******t,int I,int J,int K,int L,int M,int N){
    /*** Variables ***/
    int ******tensor = NULL;
    int i,ii,iii,iv,v,vi;
    
    /*** Espacio para puntero de 6 dimensiones ***/
    tensor = (int******)malloc(I*sizeof(int*****));
    if(tensor==NULL) return 1;
    
    
    /*** Espacio para punteros de 5 dimensiones ***/
    for(i=0;i<I;i++){
        tensor[i] = (int*****)malloc(J*sizeof(int****));
        if(tensor[i]==NULL){
            LiberaTensor(&tensor,I,J,K,L,M);
            return 1;
        }
        /*** Espacio para punteros de 4 dimensiones ***/
        for(ii=0;ii<J;ii++){
            tensor[i][ii] = (int****)malloc(K*sizeof(int***));
            if(tensor[i][ii]==NULL){
                LiberaTensor(&tensor,I,J,K,L,M);
                return 1;
            }
            /*** Espacio para punteros de 3 dimensiones ***/
            for(iii=0;iii<K;iii++){
                tensor[i][ii][iii] = (int***)malloc(L*sizeof(int**));
                if(tensor[i][ii][iii]==NULL){
                    LiberaTensor(&tensor,I,J,K,L,M);
                    return 1;
                }
                /*** Espacio para punteros de 2 dimensiones ***/
                for(iv=0;iv<L;iv++){
                    tensor[i][ii][iii][iv] = (int**)malloc(M*sizeof(int*));
                    if(tensor[i][ii][iii][iv]==NULL){
                        LiberaTensor(&tensor,I,J,K,L,M);
                        return 1;
                    }
                    /*** Espacio para punteros de una dimension ***/
                    for(v=0;v<M;v++){
                        tensor[i][ii][iii][iv][v] = (int*)malloc(N*sizeof(int));
                        if(tensor[i][ii][iii][iv][v]==NULL){
                            LiberaTensor(&tensor,I,J,K,L,M);
                            return 1;
                        }
                        /*** Llenamos las celdas ***/
                        for(vi=0;vi<N;vi++)
                            tensor[i][ii][iii][iv][v][vi] = CambioDeVelocidad();
                    }
                }
            }
        }
    }
    *t = tensor;
    return 0;
}

int ImprimeTensor(int *******t,int I,int J,int K,int L,int M,int N){
    if(*t == NULL) return 1;
    
    /*** Variables ***/
    int ******tensor = *t;
    int i,ii,iii,iv,v,vi;
    
    /*** Liberacion de memoria ***/
    for(i=0;i<I;i++)
        for(ii=0;ii<J;ii++)
            for(iii=0;iii<K;iii++)
                for(iv=0;iv<L;iv++)
                    for(v=0;v<M;v++){
                        for(vi=0;vi<N;vi++)
                            printf("%d ",tensor[i][ii][iii][iv][v][vi]);
                        printf("\n");
                    }
    
    return 0;
}

int LiberaTensor(int *******t,int I,int J,int K,int L,int M){
    if(*t == NULL) return 1;
    
    /*** Variables ***/
    int ******tensor = *t;
    int i,ii,iii,iv,v;
    
    /*** Liberacion de memoria ***/
    for(i=0;i<I;i++){
        if(tensor[i] == NULL) break;
        for(ii=0;ii<J;ii++){
            if(tensor[i][ii] == NULL) break;
            for(iii=0;iii<K;iii++){
                if(tensor[i][ii][iii] == NULL) break;
                for(iv=0;iv<L;iv++){
                    if(tensor[i][ii][iii][iv] == NULL) break;
                    for(v=0;v<M;v++)
                        if(tensor[i][ii][iii][iv][v] == NULL) break;
                        else free(tensor[i][ii][iii][iv][v]);
                    free(tensor[i][ii][iii][iv]);
                }free(tensor[i][ii][iii]);
            } free(tensor[i][ii]);
        } free(tensor[i]);
    }free(tensor);
    
    *t = NULL;
    return 0;
}

int CambioDeVelocidad(){
    return rand() % 2;
}

