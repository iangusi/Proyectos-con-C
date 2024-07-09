#ifndef ELEMENTO_H
#define ELEMENTO_H

typedef struct elemento{
    int valor;
}t_elemento,*Elemento;

int CreaElemento(Elemento*);
int EscribeElemento(Elemento,int);
int ObtieneElemento(Elemento,int*);
int DestruyeElemento(Elemento*);

#endif