#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define CONT 10

typedef struct nodo{
         int info;
         struct nodo *esq,*dir;
          }Arvore;

// Funções para lista Ordenada

Arvore* inserir(Arvore*, int);

int buscar(Arvore *raiz, int num);

Arvore* retirar(Arvore *raiz, int num);

void em_ordem(Arvore *raiz);

void pre_ordem(Arvore *raiz);

void post_ordem(Arvore *raiz);

void print2D(Arvore *raiz);

void print2DUtil(Arvore *raiz, int espaco);



int main()
{   Arvore *raiz = NULL;
    int num;
    char op;
    for(;;)
    {
        system("cls || clear");

        printf("\n----------------------------------");
        printf("\n    ARVORE DE BUSCA BINARIA\n\n");
        printf("\n I: Inserir um elemento");
        printf("\n B: Buscar um elemento");
        printf("\n R: Retirar un elemento");
        printf("\n E: Imprimir Em-Ordem");
        printf("\n P: Imprimir Pre-Ordem");
        printf("\n U: Imprimir Post-Ordem");
        printf("\n D: Imprimir 2D");
        printf("\n S: Sair");
        printf("\n\n\n Digite sua opcao: ");
        scanf("%c",&op);
        if (islower(op))op =toupper(op);

        switch (op)
        {
        case 'I': printf("\n-----Inserir-----\n");
                    printf("\n Digite um numero: ");
                    scanf("%d", &num);
                    raiz = inserir(raiz, num);
                    break;
        case 'B': printf("\n-----Buscar-----\n");
                    printf("\n Digite um numero: ");
                    scanf("%d", &num);
                    if ( buscar(raiz,num)== 0) printf("\n O numero nao encontra-se na arvore");
                    else printf("\n O numero encontra-se na arvore");
                    printf("\n\n ");
                    system("pause");
                    break;
        case 'R': printf("\n-----Retirar-----\n");
                    printf("\n Digite um numero: ");
                    scanf("%d", &num);
                    raiz = retirar(raiz,num);
                    printf("\n\n ");
                    system("pause");
                    break;
        case 'E': printf("\n-----Em-Ordem-----\n");
                    em_ordem(raiz);
                    printf("\n\n ");
                    system("pause");
                    // sleep();
                    break;
        case 'P': printf("\n-----Pre-Ordem-----\n");
                    pre_ordem(raiz);
                    printf("\n\n ");
                    system("pause");
                    break;
        case 'U': printf("\n-----Post-Ordem-----\n");
                    post_ordem(raiz);
                    printf("\n\n ");
                    system("pause");
                    break;
        case 'D': printf("\n-----Arvore 2D-----\n");
                    print2D(raiz);
                    printf("\n\n ");
                    system("pause");
                    break;
        case 'S': exit(1);

        }
    }






    return 0;
}
//*********************************************
//   Funções
//*********************************************
// Inserir um elemento na arvore binaria


 Arvore* inserir( Arvore* raiz, int num) {
    // se a arvore esta vazia retorna um unico nodo
 if (raiz == NULL) {
     raiz =(Arvore *)malloc(sizeof(Arvore));
     if( raiz == NULL)exit(1);
     raiz->info =num;
     raiz->esq = NULL;
     raiz->dir = NULL;

 return(raiz);
 }
 else {
 // senao percorre a arvore recursivamente
 if (num < raiz->info) raiz->esq = inserir(raiz->esq, num);
 else if ( num > raiz->info) raiz->dir = inserir(raiz->dir, num);
      else {printf("\nERRO numero repetido\n");
            system("pause");}
 return(raiz); // retorna a raiz sem mudar
 }
}


int buscar(Arvore *raiz,int num){
    if (raiz == NULL)  return 0;
    if(raiz->info == num) return 1;
    if (num < raiz->info) return(buscar(raiz->esq,num));
    else return(buscar(raiz->dir,num));

}

Arvore *substitui ( Arvore *raiz, Arvore *sucessor)
{ Arvore *ret;
   if ((sucessor->esq)==NULL)
   {  raiz->info=sucessor->info;
      ret=sucessor;
      sucessor=sucessor->dir;
      free(ret);
   }
   else
      sucessor->esq=substitui(raiz, sucessor->esq);
   return(sucessor);
}


Arvore* retirar(Arvore* raiz, int num)
{ Arvore *ret;
  if (raiz != NULL)
    if (raiz->info < num)
       raiz->dir=retirar(raiz->dir, num);
    else
    { if (raiz->info > num)
      raiz->esq=retirar(raiz->esq,num);
      else
      {
        if ((raiz->esq)==NULL)
        {   ret=raiz;
            raiz=raiz->dir;
            free(ret);
        }
        else
          if (raiz->dir==NULL)
          {   ret=raiz;
              raiz=raiz->esq;
              free(ret);
           }
           else
               raiz->dir=substitui(raiz, raiz->dir);
        }
    }
  return(raiz);
  }



//**************************************************
//                Funções para Percorrer a Arvore
//**************************************************

void em_ordem(Arvore *raiz){
if (raiz == NULL) return;
   em_ordem(raiz->esq);
   printf("%d ", raiz->info);
   em_ordem(raiz->dir);

}

void pre_ordem(Arvore *raiz){
   if (raiz == NULL) return;
   printf("%d ", raiz->info);
   pre_ordem(raiz->esq);
   pre_ordem(raiz->dir);

}
void post_ordem(Arvore *raiz){
   if (raiz == NULL) return;
   post_ordem(raiz->esq);
   post_ordem(raiz->dir);
   printf("%d ", raiz->info);
}

//********************************************************************
//    Impressão 2D
//********************************************************************
// função que prepara a chamada da função print2Util
void print2D(Arvore *raiz)
{
    print2DUtil(raiz, 0);
}
// Função para imprimir a arvore em 2d
//  percurso dir-raiz-esq
void print2DUtil(Arvore *raiz, int espaco)
{
    // Base case
    if (raiz == NULL)
        return;

    // aumenta distancia entre os niveis
    espaco += CONT;

    // processa dir primeiro
    print2DUtil(raiz->dir, espaco);

    // Imprime o nodo depois do espaço
    printf("\n");

    for (int i = CONT; i < espaco; i++)
        printf(" ");
    printf("%d\n", raiz->info);

    print2DUtil(raiz->esq, espaco);
}
