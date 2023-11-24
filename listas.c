#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    /* data */
    int info;
    struct nodo *prox;
    struct nodo *ant;
    
}Nodo; 

void enfileirar(Nodo **ini, int n);
void desenfileirar(Nodo **ini);
void listar(Nodo **ini); 
void limpar(Nodo **ini);

int main()
{
   Nodo *inicio= NULL;
   int num, op;
   while(1)
   {
    printf("\n"); 
    printf("\n----------MENU----------\n"); 
    printf("1. Listar a fila;\n");
    printf("2. Enfileirar;\n");
    printf("3. Desenfileirar;\n");
    printf("4. Sair;\n"); 
    printf("Escolha entre as opções:\n");
    scanf("%d", &op);
    system("clear");
    switch (op)
    {
    case 1:
        listar(&inicio);
        break;
    case 2:
        printf("\nInforme o número: ");
        scanf("%d", &num);
        enfileirar(&inicio, num);
        break;
    case 3: 
        desenfileirar(&inicio);
        break;
    case 4: 
        limpar(&inicio);
        exit(0);
        break; 
    default:
        break;
    }
   }
 

}

void enfileirar(Nodo **ini, int n)
{
    Nodo *aux, *novo;
    aux = novo = NULL;
    /* alocar espaço */
    novo = (Nodo*)malloc(sizeof(Nodo));

    if (novo == NULL)
    {
        printf("Espaço não foi criado!\n");
        return; 
    }
    novo->info = n; 
    novo->prox = novo->ant = NULL; 
    /* checar se a fila está vazia */
    if((*ini) == NULL)
    {
        *ini = novo; //add no inicio da fila
    }
    else
    {
        aux = *ini; 
        while(aux->prox!=NULL && novo->info > aux->info)
        {
            /* percorrendo */
            aux = aux->prox;
        }
        /* inserir no final */
        if(aux->prox==NULL && novo->info > aux->info)
        {
            printf("NO FINAL\n"); 
            aux->prox = novo;
            novo->ant = aux;
            novo->prox = NULL; 
        }
        else if(aux == *ini)
        {
            printf("NO INICIO");
            novo->prox = *ini;
            novo->ant =  NULL; 
            (*ini)->ant = novo;
            (*ini) = novo; 
        }
        /*inserir no meio*/
        else
        {
            printf("NO MEIO\n");
            novo->prox = aux;
            novo->ant = aux->ant;
            novo->ant->prox = novo;
            aux->ant = novo; 
        }
        

    }
}

void desenfileirar(Nodo **ini)
{
    /* fila retira do inicio */
    Nodo *aux;
    /* guardar o inicio */
    aux = *ini;
    /* checar se a fila está vazia */
    if(aux == NULL)
    {
        printf("\nA fila está vazia!\n");
        return;
    }
    /* mover o inicio */
    *ini = (*ini)->prox;
    /* desvincular da lista e limpar */
    aux ->prox = NULL;
    free(aux); 

}

void listar(Nodo **ini)
{
    Nodo *aux;
    aux = *ini;

    /* checar se a fila está vazia */
    if (aux==NULL)
    {
        printf("\nA fila está vazia!\n");
        return;
    }
    while(aux!=NULL)
    {
        /* imprime o valor */
        printf("\n %d", aux->info);
        /* move o aux */
        aux = aux->prox; 
    }
}

void limpar(Nodo **ini)
{
    Nodo *aux;
    aux = *ini;
    if(aux==NULL)
    {
        printf("\nA fila está vazia!\n");
        return;
    }
    while(aux!=NULL)
    {
        desenfileirar(&aux); 
    }
}