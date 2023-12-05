#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define NOME_ARQUIVO "perguntas_e_destinos.txt"

/*  programa que escolhe os destinos das viagens */
typedef struct cidade{
    int id;
    int turista1;
    int turista2; 
    struct cidade *cidadeProx;
}Cidade;

typedef struct pais{
    char nome[20];
    int turista1;
    int turista2; 
    struct pais *paisProx;
    Cidade *listaCidades;
}Pais;

typedef struct arvore{
    int id, cont;
    struct arvore *sim, *nao; /* sim = esq, nao=dir */
}Arvore; 

Cidade *criarCidade(int id);

Pais *criarPais(char *paisNome);

void insereCidade(Cidade **listaCidades, Cidade *cidadeNova);

void inserePais(Pais **listaPaises, Pais *paisNovo); 

void imprimePais(Pais *pais, int debug); 

void imprimeCidade(Cidade *cidade, int debug); 

void imprimeListaPaises(Pais *listaPaises, int debug);

int escolheDestino(Arvore *raiz); 

Cidade *buscarCidade(Pais *listaPaises, int id);

Arvore *inserirNodos(Arvore *raiz, int n);

Arvore *criarArvore(Arvore *raiz);

void em_ordem(Arvore *raiz); 

void lerPerguntaOuDestino(int id, char *string); 

void prepararEstruturas(Arvore **raiz, Pais **listaPaises);

void prepararPaisesECidades(Pais **listaPaises);

void prepararArvore(Arvore **raiz);

void menu(Arvore *raiz, Pais **listaPaises);

void addCliente(int id, Cidade *destino, int tipoCliente); 

void imprimeImg(char *nomeArq);

int main()
{    
    Pais *listaPaises = NULL;
    Arvore *raiz = NULL; 

    prepararEstruturas(&raiz, &listaPaises);

    menu(raiz, &listaPaises);

    return 0; 
}

void prepararEstruturas(Arvore **raiz, Pais **listaPaises)
{
    prepararPaisesECidades(listaPaises);

    prepararArvore(raiz);
}

void menu(Arvore *raiz, Pais **listaPaises)
{
    
    puts("|--------------AGÊNCIA DE VIAGENS--------------|");
    char escolha; 
    int op; 
    printf("\n\n"); 
    imprimeImg("aviao1.txt"); 
    printf("\n\n"); 
    /* mostrar a lista de destinos possíveis */
    imprimeListaPaises(*listaPaises, 0);
    printf("\n\n"); 
    printf("Aperte 1 caso já saiba qual é o destino da sua viagem.\n");
    printf("Aperte 2 caso ainda esteja indeciso.\n"); 
    scanf("%d", &op); 
    getchar(); 
    while(op==1 || op==2)
    {
        if(op==1)
        {
            /* já escolheu o destino */
            printf("Informe o destino ");
        }
        if(op==2)
        {
            /* vai escolher o destino */
            int escolhaId = 0;
            escolhaId = escolheDestino(raiz); 
            Cidade *cidadeEscolhida = buscarCidade(*listaPaises, escolhaId);
            addCliente(escolhaId, cidadeEscolhida, 2); 
            imprimeCidade(cidadeEscolhida, 0);
        }
        
        printf("Obriga pela preferência!");
        printf("Deseja continuar?(s/n)");
        scanf("%c", &escolha); 
        getchar(); 
        if(escolha=='s')
        {
            printf("Aperte 1 caso já saiba qual é o destino da sua viagem.\n");
            printf("Aperte 2 caso ainda esteja indeciso.\n"); 
            scanf("%d", &op); 
            getchar(); 
        }
        else
        {
            printf("Finalizando...\n"); 
            op=0; 
        }
    }

}

void prepararPaisesECidades(Pais **listaPaises)
{
    //ver jeito melhor pq esse ta bomba
    Pais *brasil = criarPais("Brasil");
    Cidade *salvador = criarCidade(13);
    insereCidade(&(brasil->listaCidades), salvador);
    Cidade *rio_de_janeiro = criarCidade(15);
    insereCidade(&(brasil->listaCidades), rio_de_janeiro);

    inserePais(listaPaises, brasil);

    Pais *japao = criarPais("Japão");
    Cidade *toquio = criarCidade(25);
    insereCidade(&(japao->listaCidades), toquio);

    inserePais(listaPaises, japao);
}

void prepararArvore(Arvore **raiz)
{
    /* insere o primeiro nó */
    *raiz = criarArvore(*raiz); 
    /* insere o resto dos nós */
    *raiz = criarArvore(*raiz); 
    em_ordem(*raiz); 
    printf("\n\n");
}

Cidade *buscarCidade(Pais *listaPaises, int id)
{
    Cidade *cidadeEscolhida = NULL;

    Pais *paisAtual = listaPaises;
    while(paisAtual != NULL)
    {
        Cidade *cidadeAtual = paisAtual->listaCidades;

        while (cidadeAtual != NULL)
        {
            if(cidadeAtual->id == id)
            {
                cidadeEscolhida = cidadeAtual;
                return cidadeEscolhida;
            }
            cidadeAtual = cidadeAtual->cidadeProx;
        }

        paisAtual = paisAtual->paisProx;
    }
}

void addCliente(int id, Cidade *destino, int tipoCliente)
{
    /* recebe o id do destino e atualiza na lista */
    if(destino==NULL)
    {
        return; 
    }
    /* verificar o id */
    if(destino->id==id)
    {
        if(tipoCliente==1)
        {
            /* incrementa o tipo 1 (cliente decidido) */
            destino->turista1++;
        }
        if(tipoCliente==2)
        {
            /* incrementa o tipo 2 (clientes indecisos) */
            destino->turista2++; 
        }   
    }
}

void inserePais(Pais **listaPaises, Pais *paisNovo)
{
    Pais *aux = NULL;
    aux = *listaPaises; 

    /* inserir no inicio */
    if(*listaPaises == NULL)
    {
        (*listaPaises) = paisNovo; 
    }
    else
    {
        while(aux->paisProx!=NULL)
        {
            aux = aux->paisProx;
        }
        aux->paisProx = paisNovo;
    }
}

void imprimePais(Pais *pais, int debug)
{
    if(pais == NULL)
    {
        puts("País está nulo\n");
        return;
    }
    if(pais->listaCidades == NULL)
    {
        puts("País sem cidades\n");
        return;
    }

    printf("-> %s\n", pais->nome);

    Cidade *cidadeAtual = pais->listaCidades;
    
    while(cidadeAtual != NULL)
    {   
        imprimeCidade(cidadeAtual, debug);
        cidadeAtual = cidadeAtual->cidadeProx;
    }
    puts("");
}

void imprimeCidade(Cidade *cidade, int debug)
{
    if(cidade == NULL)
    {
        puts("Cidade está nula\n");
        return;
    }

    char nome[20];
    lerPerguntaOuDestino(cidade->id, nome);
        puts("  |");
        printf("  --> %s", nome); 

    if(debug)
    {
        printf("(tipo 1: %d, tipo 2: %d)", cidade->turista1, cidade->turista2); 
    }
    puts("");
}

void imprimeListaPaises(Pais *paises, int debug)
{
    Pais *paisAtual = NULL; 
    paisAtual = paises;

    if(paises == NULL)
    {
        printf("A lista está vazia!\n");
        return;
    }
    while(paisAtual != NULL)
    {
        imprimePais(paisAtual, debug); 
        paisAtual = paisAtual->paisProx; 
    }
}

Pais *criarPais(char *paisNome)
{
    Pais *pais;
    pais = (Pais*)malloc(sizeof(Pais)); 

    if(pais==NULL)
    {
        printf("Espaço de memória não foi criado!\n");
        return NULL; 
    }

    strcpy(pais->nome, paisNome);
    pais->paisProx = NULL;
    pais->listaCidades = NULL;
    pais->turista1 = 0;
    pais->turista2 = 0;

    return pais;
}

void insereCidade(Cidade **listaCidades, Cidade *cidadeNova)
{
    Cidade *cidadeAtual = NULL;
    cidadeAtual = *listaCidades; 

    /* inserir no inicio */
    if(*listaCidades == NULL)
    {
        (*listaCidades) = cidadeNova; 
    }
    else
    {
        while(cidadeAtual->cidadeProx!=NULL)
        {
            cidadeAtual = cidadeAtual->cidadeProx;
        }
        cidadeAtual->cidadeProx = cidadeNova;
    }
}

Cidade *criarCidade(int id)
{
    Cidade *cidade;
    cidade = (Cidade*)malloc(sizeof(Cidade)); 

    if(cidade==NULL)
    {
        printf("Espaço de memória não foi criado!\n");
        return NULL; 
    }

    cidade->id = id;
    cidade->cidadeProx = NULL;
    cidade->turista1 = 0;
    cidade->turista2 = 0;

    return cidade;
}

int escolheDestino(Arvore *raiz)
{
    char resposta; 
    int id; 
    if(raiz==NULL)
    {
        return 0; 
    }
    
    /* verificar se é uma folha */
    if(raiz->sim !=NULL && raiz->nao!=NULL)
    {
        /* acessa a primeira pergunta id 16 */
        char pergunta[200];
        lerPerguntaOuDestino(raiz->id, pergunta); 
        printf("%s\n", pergunta);
        scanf("%c", &resposta); 
        getchar(); 
        switch (resposta)
        {
        case 's':
            id = escolheDestino(raiz->sim);
            break;
        case 'n':
            id = escolheDestino(raiz->nao);
            break;
        default:
            break;
        }
        return id;
    }
    else
    {
        /* se for folha, retorna o local (id do destino) */
        char destino[200];
        lerPerguntaOuDestino(raiz->id, destino);
        return raiz->id; 
    }
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
                return NULL;
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

void lerPerguntaOuDestino(int id, char *string)
{
    /* acessa o arquivo de perguntas */
    FILE *ptr=NULL;
    char retorno[200];
    int idLido = 0; 
    ptr = fopen(NOME_ARQUIVO, "rt"); 
    if(ptr==NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }
    /* percorrer o arquivo */
    while(!(feof(ptr)))
    {
        fscanf(ptr, "%d %[^\n]s", &idLido, retorno); 
        if(id == idLido) 
        {
            strcpy(string, retorno);
        }
    }
    fclose(ptr); 
}

void em_ordem(Arvore *raiz)
{
if (raiz == NULL) return;
   em_ordem(raiz->sim);
   printf("%d ", raiz->id);
   em_ordem(raiz->nao);

}

void imprimeImg(char *nomeArq)
{
    FILE *ptr=NULL;
    char file[50];
    char linha[200];
    strcpy(file, nomeArq); 
    ptr = fopen(file, "rt");
    if(ptr==NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    /* imprimir texto */
    while(!feof(ptr))
    {
        fscanf(ptr, "%[^\n]s*c", linha); 
        getc(ptr);
        printf("%s\n", linha); 
    }
    fclose(ptr);
}
