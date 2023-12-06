#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define NOME_ARQUIVO "perguntas_e_destinos.txt"
#define QTD_CIDADES 16
#define TAM_NOME 200

/*  
    programa que escolhe os destinos das viagens 
    Alunos: Alan Vitor de Almeida Nascimento, Tatiana Ribeiro Oliveira
*/
typedef struct cidade{
    int id;
    char nome[TAM_NOME];
    int turista1;
    int turista2; 
    struct cidade *cidadeProx;
}Cidade;

typedef struct pais{
    char nome[TAM_NOME];
    int turista1;
    int turista2; 
    struct pais *paisProx;
    Cidade *listaCidades;
}Pais;

typedef struct arvore{
    int id, cont;
    /* sim = esq, nao=dir */
    struct arvore *sim, *nao; 
}Arvore; 

typedef struct  nodo
{
    char nome[100]; 
    struct nodo *prox; 
}Nodo;

Cidade *criarCidade(int id, char* nome);

Pais *criarPais(char *paisNome);

void insereCidade(Cidade **listaCidades, Cidade *cidadeNova);

void inserePais(Pais **listaPaises, Pais *paisNovo); 

void imprimePais(Pais *pais, int debug); 

void imprimeCidade(Cidade *cidade, int debug); 

void imprimirDestinoEscolhido(Pais *listaPaises, Cidade *cidade);

Pais *buscarPaisPorNome(Pais *listaPaises, char *nomeCidade);

Pais *buscarPaisPorCidade(Pais *listaPaises, int idCidade);

void atenderTipo1(Pais* listaPaises);

void atenderTipo2(Pais* listaPaises, Arvore *raiz);

void imprimeListaPaises(Pais *listaPaises, int debug);

int escolheDestino(Arvore *raiz); 

Cidade *buscarCidadePorId(Pais *listaPaises, int id);

Cidade *buscarCidadePorNome(Pais *listaPaises, char *nomeCidade);

Arvore *inserirNodos(Arvore *raiz, int n);

Arvore *criarArvore(Arvore *raiz);

void em_ordem(Arvore *raiz); 

void lerPerguntaOuDestino(int id, char *string); 

void prepararEstruturas(Arvore **raiz, Pais **listaPaises);

void prepararPaisesECidades(Pais **listaPaises);

void prepararArvore(Arvore **raiz);

void menu(Arvore *raiz, Pais **listaPaises);

void addCliente(Cidade *destino, int tipoCliente); 

void imprimeImg(char *nomeArq);

/* funções para fazer 

    listar todos os paises visitados pelos turistas tipo 1
    listar todos os paises visitados pelos turistas tipo 2
    listar todos os paises visitados no total
    listar todos os paises não visitados
    mostrar o país e o sítio mais visitado pelos dois tipos de clientes

*/
void printFotoSitio(int id); 
void contarClientes(Pais *listaPaises, int tipo);

int main()
{    
    Pais *listaPaises = NULL;
    Arvore *raiz = NULL; 

    system("cls||clear");

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
    int op = 1; 
    while(op==1 || op==2)
    {
        puts("|--------------------AGÊNCIA DE VIAGENS-------------------|");
        char escolha; 
     
        printf("\n\n"); 
        imprimeImg("aviao1.txt"); 
        printf("\n\n"); 
        printf("\n\n"); 
        printf("Aperte 1 caso já saiba qual é o destino da sua viagem.\n");
        printf("Aperte 2 caso ainda esteja indeciso.\n"); 
        printf("Aperte 3 para sair.\n");
        scanf("%d", &op); 
        getchar(); 

        if(op==1)
        {
            atenderTipo1(*listaPaises);
        }
        if(op==2)
        {
            atenderTipo2(*listaPaises, raiz);
        }
        
        printf("\n\nObrigado pela preferência!\n\n");
    }
    contarClientes(*listaPaises, 1); 
    contarClientes(*listaPaises, 2); 
    contarClientes(*listaPaises, 3);
    contarClientes(*listaPaises, 0);
    contarClientes(*listaPaises, 4);

}

void atenderTipo1(Pais *listaPaises)
{
    system("cls||clear");
    /* Exibe a lista e recebe destino desejado */

    Cidade *cidade = NULL;
    char nomeDestinoUsuario[200];
    while(cidade == NULL)
    {
        imprimeListaPaises(listaPaises, 0);

        printf("Informe o destino (nome da cidade): ");

        scanf("%[^\n]", nomeDestinoUsuario);
        while (getchar() != '\n'); //limpa buffer 

        cidade = buscarCidadePorNome(listaPaises, nomeDestinoUsuario);
        
        if(cidade == NULL)
        {
            system("cls||clear");
            puts("Cidade não existe no catálogo. ");
            puts("Aperte qualquer tecla para tentar novamente.");
            getchar();
        }
    }           

    addCliente(cidade, 1);  
    
    imprimirDestinoEscolhido(listaPaises, cidade);
    printFotoSitio(cidade->id); 
}

void atenderTipo2(Pais *listaPaises, Arvore* raiz)
{
    system("cls||clear");
    /* Roda a arvore de decisão */

    int escolhaId = 0;

    escolhaId = escolheDestino(raiz); 
    
    Cidade *cidadeEscolhida = buscarCidadePorId(listaPaises, escolhaId);

    addCliente(cidadeEscolhida, 2); 

    imprimirDestinoEscolhido(listaPaises, cidadeEscolhida);

    printFotoSitio(cidadeEscolhida->id); 
}

void prepararPaisesECidades(Pais **listaPaises)
{

    /* acessa o arquivo de perguntas */
    FILE *ptr=NULL;

    ptr = fopen(NOME_ARQUIVO, "rt"); 
    if(ptr==NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    /* percorrer o arquivo */
    char buffer[TAM_NOME];
    char nomePais[TAM_NOME];
    char nomeCidade[TAM_NOME];
    int idCidade = -1;
    int contador = 1;
    while(!(feof(ptr)))
    {
       
        if(contador%2 == 1)
        {
            fscanf(ptr, "%d %[^,], %[^\n]\n", &idCidade, nomePais, nomeCidade); 

            Cidade *cidadeNova = criarCidade(idCidade, nomeCidade);

            Pais *paisExistente = buscarPaisPorNome(*listaPaises, nomePais);
            if(paisExistente != NULL)
            {
                insereCidade(&(paisExistente->listaCidades), cidadeNova);   
            }
            else
            {
                Pais *paisNovo = criarPais(nomePais);
                insereCidade(&(paisNovo->listaCidades), cidadeNova);
                inserePais(listaPaises, paisNovo);
            }
        }
        else
        {
            fscanf(ptr, "%[^\n]s", buffer);
        }
        contador++;
    }
    
}

void prepararArvore(Arvore **raiz)
{
    /* insere o primeiro nó */
    *raiz = criarArvore(*raiz); 
    /* insere o resto dos nós */
    *raiz = criarArvore(*raiz); 
    // em_ordem(*raiz); 
    printf("\n\n");
}

Cidade *buscarCidadePorId(Pais *listaPaises, int id)
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

    return NULL;
}

Cidade *buscarCidadePorNome(Pais *listaPaises, char *nomeCidade)
{
    Cidade *cidadeEscolhida = NULL;

    Pais *paisAtual = listaPaises;
    while(paisAtual != NULL)
    {
        Cidade *cidadeAtual = paisAtual->listaCidades;

        while (cidadeAtual != NULL)
        {
            if(strcmp(nomeCidade, cidadeAtual->nome) == 0)
            {
                cidadeEscolhida = cidadeAtual;
                return cidadeEscolhida;
            }
            cidadeAtual = cidadeAtual->cidadeProx;
        }

        paisAtual = paisAtual->paisProx;
    }

    return NULL;
}

void addCliente(Cidade *destino, int tipoCliente)
{
    /* recebe o id do destino e atualiza na lista */
    if(destino==NULL)
    {
        return; 
    }

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

    puts("  |");
    printf("  --> %s", cidade->nome); 

    if(debug)
    {
        printf("(tipo 1: %d, tipo 2: %d)", cidade->turista1, cidade->turista2); 
    }
    puts("");
}

void imprimirDestinoEscolhido(Pais* listaPaises, Cidade *cidade)
{
    system("clear||cls");
    Pais *pais = buscarPaisPorCidade(listaPaises, cidade->id);
    printf("\n\n%s\n", pais->nome);
    imprimeCidade(cidade, 0);
    puts("");
}

Pais *buscarPaisPorNome(Pais *listaPaises, char *nome)
{
    Pais *paisAtual = listaPaises;
    Pais *paisEscolhido = NULL;

    if(listaPaises == NULL)
    {
        // puts("Lista de países vazia");
        return NULL;
    }

    while(paisAtual != NULL)
    {
        if(strcmp(paisAtual->nome, nome) == 0)
        {
            paisEscolhido = paisAtual;
            return paisEscolhido;
        }
        paisAtual = paisAtual->paisProx;
    }

    return NULL;
}

Pais *buscarPaisPorCidade(Pais *listaPaises, int idCidade)
{
    if(listaPaises == NULL)
    {
        // puts("Lista de paises vazia");
        return NULL;
    }
    
    Cidade *cidadeEscolhida = NULL;

    Pais *paisAtual = listaPaises;
    while(paisAtual != NULL)
    {
        Cidade *cidadeAtual = paisAtual->listaCidades;

        while (cidadeAtual != NULL)
        {
            if(cidadeAtual->id == idCidade)
            {
                return paisAtual;
            }
            cidadeAtual = cidadeAtual->cidadeProx;
        }
        paisAtual = paisAtual->paisProx;
    }
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

Cidade *criarCidade(int id, char *nome)
{
    Cidade *cidade;
    cidade = (Cidade*)malloc(sizeof(Cidade)); 

    if(cidade==NULL)
    {
        printf("Espaço de memória não foi criado!\n");
        return NULL; 
    }

    cidade->id = id;
    strcpy(cidade->nome, nome);
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
        char pergunta[TAM_NOME];
        lerPerguntaOuDestino(raiz->id, pergunta); 

        while(resposta != 's' && resposta != 'n')
        {
            printf("\n%s\n\n", pergunta);
            scanf("%c", &resposta); 
            while(getchar() != '\n');

            
            if(resposta != 's' && resposta != 'n')
            {
                puts("Utilize somente 's' ou 'n' para responder");
            }
        }
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
        char destino[TAM_NOME];
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
    char retorno[TAM_NOME];
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
            fclose(ptr); 
            return;
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

void imprimeImg(char *nomeArq)
{
    FILE *ptr=NULL;
    char file[50];
    char linha[TAM_NOME];
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

void printFotoSitio(int id)
{
    /* recebe o id do destino e imprime a imagem correspondente */
    switch (id)
    {
    case 1:
        /* Macchu Picchu */
        imprimeImg("montanha.txt");
        break;
    case 3: 
        /* Pequim */
        imprimeImg("cidade2.txt");
        break;
    case 5:
        /* Niagara Falls */
        imprimeImg("cataratas.txt");
        break;
    case 7: 
        /* Interlaken */
        imprimeImg("montanha2.txt");
        break;
    case 9:
        /* cancún */
        imprimeImg("praia.txt");
        break;
    case 11:
        /* punta cana */
        imprimeImg("praia3.txt");
        break;
    case 13:
        /* salvador */
        imprimeImg("praia2.txt");
        break;
    case 15:
        /* rio de janeiro */
        imprimeImg("cidade.txt");
        break;
    case 17:
        /* roma */
        imprimeImg("escultura.txt");
        break;
    case 19:
        /* atenas */
        imprimeImg("templo.txt");
        break;
    case 21:
        /* barcelona */
        imprimeImg("cidade3.txt");
        break;
    case 23:
        /* sydney */
        imprimeImg("cidade4.txt");
        break;
    case 25:
        /* tóquio */
        imprimeImg("cidade5.txt");
        break;
    case 27:
        /* ibiza */
        imprimeImg("cidade6.txt");
        break;
    case 29:
        /* dublin */
        imprimeImg("castelo.txt");
        break;
    case 31:
        /* edimburgo */
        imprimeImg("castelo2.txt");
        break;
    default:
        break;
    }
}

void contarClientes(Pais *listaPaises, int tipo)
{
    if(listaPaises==NULL)
    {
        return; 
    }
    Pais *paisAtual=NULL;
    paisAtual = listaPaises;  
    Cidade *cidadeAtual=NULL;

    Pais *paisMaisVisitado = NULL;
    int paisMaisVisitadoQntTuristas = 0;
    Cidade *cidadeMaisVisitada = NULL;
    int cidadeMaisVisitadaQntTuristas = 0;

    if(tipo==1)
    {
        /* vai listar os países com clientes do tipo 1 */
        printf("\n\n----LOCAIS VISITADOS PELOS CLIENTES TIPO 1-----\n");
    }
    if(tipo == 2)
    {
        /* vai listar os países com clientes do tipo 2 */
        printf("\n\n----LOCAIS VISITADOS PELOS CLIENTES TIPO 2-----\n");
    }
    if(tipo == 3)
    {
        /* vai listar os países visitados no geral */
        printf("\n\n----LOCAIS VISITADOS NO TOTAL-----\n");
    }
    if(tipo==0)
    {
        /* vai listar os países não visitados */
        printf("\n\n----LOCAIS NÃO VISITADOS-----\n");
    }
    while (paisAtual!=NULL)
    {
        int totalTuristasPais = 0;
        cidadeAtual = paisAtual->listaCidades;
        while (cidadeAtual!=NULL)
        {
            int totalTuristasCidade = 0;
            switch (tipo)
            {
            case 1:  
                if(cidadeAtual->turista1!=0)
                { 
                    printf("%s : %s\n", paisAtual->nome, cidadeAtual->nome); 
                }
                break;
            case 2: 
                if(cidadeAtual->turista2!=0)
                {
                    printf("%s : %s\n", paisAtual->nome, cidadeAtual->nome); 
                }
                break; 
            case 3:
                if(cidadeAtual->turista1!=0 || cidadeAtual->turista2!=0)
                {
                    printf("%s : %s\n", paisAtual->nome, cidadeAtual->nome);
                }
                break;
            case 0:
                if(cidadeAtual->turista1==0 && cidadeAtual->turista2==0)
                {
                    printf("%s : %s\n", paisAtual->nome, cidadeAtual->nome);
                }
            case 4:
                totalTuristasCidade = cidadeAtual->turista1 + cidadeAtual->turista2;
                break;
            default:
                break;
            }

            if(cidadeMaisVisitadaQntTuristas < totalTuristasCidade)
            {
                cidadeMaisVisitadaQntTuristas = totalTuristasCidade;
                cidadeMaisVisitada = cidadeAtual;
            }
            cidadeAtual = cidadeAtual->cidadeProx;
            totalTuristasPais += totalTuristasCidade;
        }
        if(paisMaisVisitadoQntTuristas < totalTuristasPais)
        {
            paisMaisVisitadoQntTuristas = totalTuristasPais;
            paisMaisVisitado = paisAtual;
        }
        paisAtual = paisAtual->paisProx;   
    }
    
    if(tipo==4)
    {
        /* vai listar os países não visitados */
        printf("\n\n----PAÍS E CIDADE MAIS VISITADOS -----\n");
        if(cidadeMaisVisitada != NULL && paisMaisVisitado != NULL)
        {
            printf("País: %s\n", paisMaisVisitado->nome);
            printf("Cidade: %s\n", cidadeMaisVisitada->nome);
        }

    }

}