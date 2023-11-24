#include <stdio.h>
#include <stdlib.h>
#include "string.h"
/*  programa que escolhe os destinos das viagens */
typedef struct nodo{
    char lugar[20];
    char tipo[10]; 
    int turista1;
    int turista2; 
    struct nodo *cidadeProx, *paisProx;

}Sitio;

typedef struct nodo{
    int id, cont;
    struct nodo *sim, *nao; 
}Arvore; 

void inserePais(Sitio **paises, Sitio **paisNovo); 
void imprimePais(Sitio *pais); 
void imprimeListaPaises(Sitio **paises);
Sitio *criarPais(char paisNome[20], char cidade1[20], char cidade2[20]); 

int escolheDestino(Arvore **raiz); 

int main()
{
    Sitio *paises = NULL;

    Sitio *pais1 = criarPais("Brasil", "Salvador", "Cuiabá");
    inserePais(&paises, &pais1); 
    Sitio *pais2 = criarPais("Japão", "toquio", "osaka"); 
    inserePais(&paises, &pais2); 
    
    imprimeListaPaises(&paises); 

    return 0; 
}

void inserePais(Sitio **paises, Sitio **paisNovo)
{
    Sitio *aux=NULL;
    aux = *paises; 

    /* inserir no inicio */
    if(*paises == NULL)
    {
        (*paises) = *paisNovo; 
    }
    else
    {
        while(aux->paisProx!=NULL)
        {
            aux = aux->paisProx;
        }
        aux->paisProx = *paisNovo;
    }

}

void imprimePais(Sitio *pais)
{
    Sitio *aux=NULL; 
    aux = pais; 
    if(aux == NULL)
    {
        printf("A lista está vazia!\n");
        return;
    }

    /* país */
    printf("%s ", aux->lugar);
    
    /* cidades */
    aux = aux->cidadeProx;
    /* cidade 1 */
    printf("%s ", aux->lugar);
    
    /* cidade 2 */
    aux = aux->cidadeProx;
    printf("%s ", aux->lugar); 
    
}

void imprimeListaPaises(Sitio **paises)
{
    Sitio *aux = NULL; 
    aux = *paises;
    if(aux == NULL)
    {
        printf("A lista está vazia!\n");
        return;
    }
    while(aux!=NULL)
    {
        imprimePais(aux); 
        printf("->"); 
        aux = aux->paisProx; 
    }
}

Sitio *criarPais(char paisNome[20], char cidade1[20], char cidade2[20])
{
    Sitio *novo1, *novo2;
    novo1 = novo2 = NULL; 
    novo1 = (Sitio*)malloc(sizeof(Sitio)); 
    novo2 = (Sitio*)malloc(sizeof(Sitio)); 
    if(novo1==NULL || novo2==NULL)
    {
        printf("Espaço de memória não foi criado!\n");
        return NULL; 
    }

    /* cidade 1 */
    novo1->cidadeProx = novo2;
    strcpy(novo1->lugar, cidade1);
    novo1->paisProx = NULL;
    strcpy(novo1->tipo, "cidade");
    novo1->turista1 = 0;
    novo1->turista2 = 0;

    /* cidade 2 */
    novo2->cidadeProx = NULL;
    strcpy(novo2->lugar, cidade2);
    novo2->paisProx = NULL;
    strcpy(novo2->tipo, "cidade");
    novo2->turista1 = 0;
    novo2->turista2 = 0;

    Sitio *pais;
    pais = (Sitio*)malloc(sizeof(Sitio)); 

    if(pais==NULL)
    {
        printf("Espaço de memória não foi criado!\n");
        return NULL; 
    }

    pais->cidadeProx = novo1;
    strcpy(pais->lugar, paisNome);
    pais->paisProx = NULL;
    strcpy(pais->tipo, "pais");
    pais->turista1 = 0;
    pais->turista2 = 0;

}
