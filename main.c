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

typedef struct arvore{
    int id, cont;
    struct arvore *sim, *nao; /* sim = esq, nao=dir */
}Arvore; 

void inserePais(Sitio **paises, Sitio **paisNovo); 
void imprimePais(Sitio *pais); 
void imprimeListaPaises(Sitio **paises);
Sitio *criarPais(char paisNome[20], char cidade1[20], char cidade2[20]); 
int escolheDestino(Arvore **raiz); 
Arvore *inserirNodos(Arvore *raiz, int n);
Arvore *criarArvore(Arvore *raiz);
void em_ordem(Arvore *raiz); 
void lerPerguntas(int id); 


int main()
{
    Sitio *paises = NULL;
    Arvore *raiz = NULL; 
    Sitio *pais1 = criarPais("Brasil", "Salvador", "Cuiabá");
    inserePais(&paises, &pais1); 
    Sitio *pais2 = criarPais("Japão", "toquio", "osaka"); 
    inserePais(&paises, &pais2); 
    imprimeListaPaises(&paises); 
    printf("\n\n"); 
    /* insere o primeiro nó */
    raiz = criarArvore(raiz); 
    /* insere o resto dos nós */
    raiz = criarArvore(raiz); 
    em_ordem(raiz); 
    printf("\n\n");
    lerPerguntas(2);

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

Arvore *inserirNodos(Arvore *raiz, int n)
{

    if(raiz==NULL)
    {
        raiz = (Arvore*)malloc(sizeof(Arvore));
        if(raiz==NULL)
        {
            exit(1);
        }
        raiz->id=n;
        raiz->sim=raiz->nao=NULL;
        return (raiz);
    }
    else
    {
        if(n < raiz->id)
        {
            /* vai para esquerda */
            raiz->sim = inserirNodos(raiz->sim, n);
        }
        else
        {
            if(n > raiz->id)
            {
                /* vai para direita */
                raiz->nao = inserirNodos(raiz->nao, n);
            }
            else
            {
                printf("Número repetido.\n");
                return;
            }
            
        }
        return (raiz);
    }
}

Arvore *criarArvore(Arvore *raiz)
{
    if(raiz == NULL)
    {
        raiz = inserirNodos(raiz, 16);
    }
    /* preenchendo os nós com os ids corretos */
    else
    {
        raiz = inserirNodos(raiz, 8);
        raiz = inserirNodos(raiz, 24);
        raiz = inserirNodos(raiz, 4);
        raiz = inserirNodos(raiz, 12);
        raiz = inserirNodos(raiz, 20);
        raiz = inserirNodos(raiz, 28);
        raiz = inserirNodos(raiz, 2);
        raiz = inserirNodos(raiz, 6);
        raiz = inserirNodos(raiz, 10);
        raiz = inserirNodos(raiz, 14);
        raiz = inserirNodos(raiz, 18);
        raiz = inserirNodos(raiz, 22);
        raiz = inserirNodos(raiz, 26);
        raiz = inserirNodos(raiz, 30);
        raiz = inserirNodos(raiz, 1);
        raiz = inserirNodos(raiz, 3);
        raiz = inserirNodos(raiz, 5);
        raiz = inserirNodos(raiz, 7);
        raiz = inserirNodos(raiz, 9);
        raiz = inserirNodos(raiz, 11);
        raiz = inserirNodos(raiz, 13);
        raiz = inserirNodos(raiz, 15);
        raiz = inserirNodos(raiz, 17);
        raiz = inserirNodos(raiz, 19);
        raiz = inserirNodos(raiz, 21);
        raiz = inserirNodos(raiz, 23);
        raiz = inserirNodos(raiz, 25);
        raiz = inserirNodos(raiz, 27);
        raiz = inserirNodos(raiz, 29);
        raiz = inserirNodos(raiz, 31);
    }

    return raiz; 

}

void lerPerguntas(int id)
{
    /* acessa o arquivo de perguntas */
    FILE *ptr=NULL;
    char pergunta[100];
    int idPergunta=0; 
    ptr = fopen("perguntas.txt", 'rt'); 
    if(ptr==NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }
    /* percorrer o arquivo */
    while(!(feof(ptr)))
    {
        fscanf(ptr, "%d %[^\n\0]s", &idPergunta, pergunta); 
        if(id == idPergunta) 
        {
            printf("%d : %s",idPergunta, pergunta);
        }
    }
}

void em_ordem(Arvore *raiz)
{
if (raiz == NULL) return;
   em_ordem(raiz->sim);
   printf("%d ", raiz->id);
   em_ordem(raiz->nao);

}