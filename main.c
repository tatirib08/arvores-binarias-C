#include <stdio.h>
#include <stdlib.h>
/*  programa que escolhe os destinos das viagens */
typedef struct nodo{
    char lugar[20];
    struct nodo *esq, *dir;
    //  struct nodo *cidadeProx, *paisProx;

}Sitio;

 /* cada lugar pode ter um id, pra ser mais facil ao inves de trabalhar com string */
Sitio* inserirNodo(Sitio **raiz, int n);
Sitio* removerNodo(Sitio **raiz); 
void imprimir(Sitio **raiz);


int main()
{
    return 0; 
}