#include <stdio.h>
#include <stdlib.h>

void imprimirMatriz(int*,int,int);
void matrizAumentada(int*,int);

void operacion(int*,int*,int,int);
void intercambio(int*,int*,int);
int mcd(int,int);

int main(){
    
    int i=0, j=0;
    int filas_columnas;
    
	//Pedimos el numero de filas y columnas
    do{
        printf("#Filas y Columnas: ");
        scanf("%d", &filas_columnas);
        __fpurge(stdin);
    }while(filas_columnas<2);
    
	//Creamos la matriz y un puntero al primer elemento de la matriz
    int matrix[filas_columnas][filas_columnas], *elemento=matrix[0];
    printf("\n");
    
	//Pedimos cada elemento de la matriz
    for(i = 0;i<filas_columnas;i++){
        for(j = 0;j<filas_columnas;j++){
            printf("Elemento[%d][%d]: ",i+1,j+1);
            scanf("%d",elemento);
            __fpurge(stdin);
            elemento++;
        }
    }
    
	//Imprimimos la matriz
    printf("\nMatriz\n");
    imprimirMatriz(matrix[0],filas_columnas,1);
    
	//Aumentamos la matriz y resolvemos
    printf("Matriz Aumentada:\n");
    matrizAumentada(matrix[0],filas_columnas);
    
    return 0;
}

void imprimirMatriz(int *matrix, int m, int n){
    for(int i = 1;i<=n*m*m;i++){
        printf("%d\t",*matrix);
        matrix++;
        if(i%(n==1 ? m:m*2) == 0)
            printf("\n");
    }
    printf("\n");
}

void matrizAumentada(int *matrix, int m){
    
    int i=0, j=0;
	//Inicializamos la matriz aumentada
    int mat[m][m*2];
    
	//LLenamos la matriz
    for(i = 0;i<m;i++){
		//Usamos la matriz que nos dieron
        for(j = 0;j<m;j++){
            mat[i][j] = *matrix;
            matrix++;
        }
		//Ponemos la matriz identidad
        for(j = m;j<m*2;j++){
            mat[i][j] = i == j-m ? 1:0;
        }
    }
    
    imprimirMatriz(mat[0],m,2);
    
    printf("Operaciones:\n");
    //El pivote nos marca la posicion de los elementos que mantendremos en cada columna
	//Mientras que los demás elementos serán convertidos en 0
	int pivote=0;
    for(pivote=0;pivote<m;pivote++){
		//¿Que pasa si uno de estos elementos es 0?
        if(mat[pivote][pivote] == 0){
            int continuar = 0;
			//Debemos buscar algun otro elemento que no sea 0
            for(i=pivote;i<m;i++){
                if(mat[i][pivote] != 0){
					//Si encontramos el elemento, intercambiamos los renglones: Ri <-> Rj
                    intercambio(mat[pivote],mat[i],m);
                    imprimirMatriz(mat[0],m,2);
                    continuar = 1;
                    break;
                }
            }
			//Si no encontramos otro elemento, entonces la matriz no tiene inversa
            if(continuar==0){
                printf("La matriz es singular");
                return;
            }
        }
        /*
		Una vez tenemos nuestro pivote, debemos convertir todos los demas elementos 
		de la columna en 0, para ello, tenemos que hacer uso de la operacion: Ri -> Ri - aRj
		*/
        for(i=0; i<m; i++){
			//Si el elemento a convertir ya esta en 0, solo se salta al siguiente
            if(i!=pivote && mat[i][pivote] != 0){
                operacion(mat[i],mat[pivote],m,pivote);
                imprimirMatriz(mat[0],m,2);
            }
        }
    }
    
    printf("Inversa de la matriz:\n");
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
			/*
			En este punto, tenemos que convertir la primera parte de la matriz
			en la matriz identidad, para ello debemos usar la operacion: Ri -> aRi
			Sin embargo, el programa nos daria decimales en lugar de fracciones
			además de que no es necesario dividir todo el renglon ya que solo hay 
			dos valores en cada renglo: el que debe ser 1, y el de la matriz inversa
			Por ello, la operacion se hara manualmente:
			*/
            int val1 = mat[i][j+m]; //Valor de matriz inversa
            int val2 = mat[i][i]; //Valor a convertir en 1
            
			//Maximo comun divisor entre ambos valores
            int d = mcd(val1,val2);
			//Los dividimos sabiendo que nos daran enteros sin decimales
            val1 /= d;
            val2 /= d;
			//Si val1 era divisible entre val2, entonces d = val2, por lo que al dividir val2=1
            if(val2==1){
				//Y nos queda un entero por respuesta en la matriz inversa
                printf("%d\t",val1);
            }else{
				//De lo contrario nos quedara una fraccion
				
				//Si val2 en negativo, al imprimir nos quedara algo como: a/-b
                if(val2<0){
					//Por lo que debemos cambiarlo a: -a/b
                    printf("-%d/%d\t",val1,abs(val2));
                }else{
					//Sino, lo imprimimos sin más complicaciónes
                    printf("%d/%d\t",val1,val2);
                }
            }
        }
        printf("\n");
		//Con esto terminamos la conversion :)
    }
}

void operacion(int *fila1, int *fila2, int m, int col){
    int i;
	/*
	Pa que se entienda mejor pondre esta parte de forma grafica con un ejemplo:
	
	m=5
	col=1    |----Elemento a convertir en 0
	fila1: 0 3 2 1 4
	fila2: 0 6 4 3 2
	         |----El otro elemento
	*/
    int elemento1=fila1[col], elemento2=fila2[col];
    for(i=0; i<2*m; i++, fila1++, fila2++){
		/*
		Para eficientar el proceso usamos el maximo comun divisor
		para evitar que la multiplicación nos de numero muy grandes.
		
		Con el ejemplo de antes:
		elemento1 = 3
		elemento2 = 6
		d = 3
		
		Al dividir:
		elemento1 = 1
		elemento2 = 2
		y entonces, multiplicar todo el renglon por 1 o 2 es mucho mejor que por 3 y 6
		*/
		int d = mcd(elemento1,elemento2);
		elemento1 /= d;
		elemento2 /= d;
        *fila1 = (*fila1*elemento2)-(*fila2*elemento1);
    }
}

void intercambio(int *fila1, int *fila2, int m){
	//Creamos una variable que servira como espacio temporal pa los elementos de la fila1
    int r, i;
    for(i=0; i<2*m; i++, fila1++, fila2++){
		//Pasamos los datos de fila1 a r
        r = *fila1;
		//Pasamos los datos de fila2 a fila1
        *fila1 = *fila2;
		//Pasamos los datos de r a fila2
        *fila2 = r;
    }
}

int mcd(int a, int b){
    if (b == 0) return a;
    return mcd(b, a % b);
}