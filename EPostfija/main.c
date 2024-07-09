#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "elemento.h"

int ExpresionPostFija(char*);
int AgregarExpresiones(char*,int*,char*);
int LiberandoPila(int,int,Pila,char*,int*,char*);
    
int main(){
    
    char *expresion = (char*)malloc(100*sizeof(char));
    if(expresion==NULL)return 1;
    printf("Ingresa la expresion infija: ");
    scanf("%s",expresion);
    __fpurge(stdin);
    
    for(int l=0;l<100;l++){
        if(expresion[l]=='\0'){
            expresion = (char*)realloc(expresion,(l+1)*sizeof(char));
            if(expresion==NULL)return 1;
            break;
        }
    } 
    
    printf("Expresion postfija: ");
    ExpresionPostFija(expresion);
    
    free(expresion);
    return 0;
}

int ExpresionPostFija(char *expresion){
    int b;
    //Creamos pila para guardar los operadores
    Pila operadores;
    b = CreaPila(&operadores);
    if(b==1)return 1;
    
    char *ex = expresion, *expresionPostFija=(char*)malloc(0);
    if(expresionPostFija==NULL) return 1;
    int longitud=0;
    
    Elemento elementos;
    char *op;
    
    //Avanzamos caracter por caracter
    for(;;ex++){
        if(*ex=='\0'){
            //Si llegamos al final de la expresion, liberamos toda la pila
            while(LiberandoPila(0,0,operadores,expresionPostFija,&longitud,ex) == 0);
            break;
            
        }else if(*ex=='+'||*ex=='-'||*ex=='*'||*ex=='/'||*ex=='^'||*ex=='('||*ex=='{'||*ex=='['){
            /*
            En caso de que aparezca alguno de estos operadores, tenemos que crear un espacio
            en memoria donde guardarlo
            */
            op = (char*)malloc(2*sizeof(char));
            op[0] = *ex;
            op[1] = '\0';
            b = CreaElemento(&elementos);
            if(b==1)return 1;
            //Necesitamos asignarle una jerarquia especifica
            int j;
            if(*ex=='+'||*ex=='-') j = 1;
            else if(*ex=='*'||*ex=='/') j = 2;
            else if(*ex=='^') j = 3;
            else if(*ex=='('||*ex=='{'||*ex=='[') j = 0;
            //Finalmente escribimos el elemento
            b = EscribeElemento(elementos,op,j);
            if(b==1)return 1;
            
            /*
            Antes de apilar el elemento, debemos ver si, ya dentro de la pila, hay
            algun elemento con una jerarquia mayor, de ser asi, se debe sacar de la pila
            */
            if(*ex=='+'||*ex=='-'||*ex=='*'||*ex=='/'||*ex=='^')
                for(;;) if(LiberandoPila(1,j,operadores,expresionPostFija,&longitud,ex) == 1)break;
            
            //Ahora si, apilamos el nuevo elemento
            b = InsertaNodoElemento(operadores,elementos);
            if(b==1)return 1;
            //ImprimePila(operadores);
            
        } else if(*ex==']'||*ex=='}'||*ex==')'){
            /*
            Ahora liberaremos la pila hasta encontrar al operador contrario
            */
            while(LiberandoPila(2,0,operadores,expresionPostFija,&longitud,ex) == 0);
            //ImprimePila(operadores);
            
        } else AgregarExpresiones(expresionPostFija,&longitud,ex);
    }
    
    printf("%s\n",expresionPostFija);
    //Liberamos memoria de la pila y de la expresionPostFija
    DestruyePila(&operadores);
    free(expresionPostFija);
    return 0;
}

int ComparaExpresiones(char *ex1, char *ex2){
    for(;;ex1++,ex2++){
        if(*ex1!=*ex2) return 1;
        if(*ex2=='\0') return 0;
    }
}

int AgregarExpresiones(char *expresionPostFija, int *longitud, char *ex){
    (*longitud)++;
    expresionPostFija=(char*)realloc(expresionPostFija,*longitud*sizeof(char));
    if(expresionPostFija==NULL) return 1;
    expresionPostFija[*longitud-1] = *ex;
    return 0;
}

int LiberandoPila(int opc, int j,Pila operadores,char *expresionPostFija,int *longitud,char *ex){
    Elemento e;
    char *el;
    int b,j2;
    
    if(ConsultaPrimero(operadores,&e) == 1) return 1;
    
    if(opc==0){
        b = QuitaNodoElemento(operadores,&e);
        if(b==1)return 2;
        b = ObtieneElemento(e,&el,&j2);
        if(b==1)return 2;
        AgregarExpresiones(expresionPostFija,longitud,el);
        if(b==1)return 2;
        DestruyeElemento(&e);
        return 0;
    }else if(opc == 1){
        ObtieneElemento(e,&el,&j2);
        if(j2>j) return LiberandoPila(0,0,operadores,expresionPostFija,longitud,ex);
    } else if(opc == 2){
        ObtieneElemento(e,&el,&j2);
        
        if(j2 != 0)
            return LiberandoPila(0,0,operadores,expresionPostFija,longitud,ex);
        
        b = QuitaNodoElemento(operadores,&e);
        if(b==1)return 2;
        DestruyeElemento(&e);
    }
    return 1;
}