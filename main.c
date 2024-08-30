/*
 * Calculadora Didática de Conversão
 * Autor: Luana Costa Lima Maynard de Arruda Falcão
 * Data de criação: [30/08/2024]
 * Última atualização: [30/08/2024 às 19:03]
 * GitHub: https://github.com/lua-mf/Calculadora-didatica-de-conversao
 * Descrição: Este programa realiza conversões de base 10 para outras bases e representações numéricas, mostrando os passos detalhados na tela.
 *
 * Revisões/Atualizações:
 * - [30/08/2024 às 18:05]: Implementação inicial.
 * - [30/08/2024 às 18:10]: Escrita do README.
 * - [30/08/2024 às 18:36]: Menu e criação das primeiras funções
 * - [30/08/2024 às 19:03]: correção do Menu
 */
#include <stdio.h>
#include <math.h>

typedef struct Node{
  char num;
  struct Node *prox;
}Node;

void add(Node **head, char n);
void imprimir(Node *head);
void conversaoBase(int n, int base, Node *head);
void BCD(int n);
void A216(int n, Node *head);
  
int main(void) {
  int resposta, n, base;
  Node *head = NULL;
  
  do{
    printf("\n==================== Cáculadora Didática de Conversão ======================\n");
    printf("[1] Conversao de decimal para binario\n");
    printf("[2] Conversao de decimal para octal\n");
    printf("[3] Conversao de decimal para hexadecimal\n");
    printf("[4] Conversao de decimal para o côdigo BCD\n");
    printf("[5] Conversao de decimal para base com sinal com 16 bits (complemento a 2)\n");
    printf("[6] Conversao de real em decimal para float e double\n");
    printf("[7] Sair \n");

    printf("\nDigite a opcao que deseja: ");      
    scanf(" %d", &resposta);
    printf("\nDigite um número inteiro decimal: ");
    scanf("%d", &n);
  
    if(resposta==1 || resposta==2 || resposta==3){
      if(resposta==1){
        base = 2;
      }else if(resposta==2){
        base = 8;
      }else if(resposta==3){
        base = 16;
      }
      conversaoBase(n, base, head);
      
    }else if(resposta==2){
      //BCD
      BCD(n);
    }else if(resposta==3){
      // base 10 para base com sinal com 16 bits
      
      
    }
  }while(resposta!=7);
  
  return 0;
}

void add(Node **head, char n){
  Node *novo = (Node*)malloc(sizeof(Node));

  if(novo!=NULL){
    novo->num = n;
    novo->prox = *head;
    *head = novo;
  }
}

void imprimir(Node *head){
  while(head!=NULL){
    if (head->num >= 'A' && head->num <= 'B') {  // Para base 16
      printf("%c", head->num);
    } else {
      printf("%d", head->num - '0');  // Converte o caractere de volta para número
    }
    head = head->prox;
  }
}

void conversaoBase(int n, int base, Node *head){
  int quociente = n, resto = 0;
  //conversões de base 10 para base 2, 8 ou 16
  while(quociente>0){
    resto = quociente%base;
    printf("\n%d/%d = %d + o resto %d", quociente , base, quociente/base, resto);
    quociente = quociente/base;
    if(base==2 || base==8){
      add(&head, '0' + resto);
    }else if(base==16){
      add(&head, 'A' + (resto - 10));
    }
  }
  printf("\n\nBase %d: ", base);
  imprimir(head);
  printf("\n");
}

void BCD(int n){
  char bcd[16];
  int i = 0;
  
  while(n>0){
    while (n > 0) {
      int digito = n % 10;  // Obtém o último dígito
      bcd[i] = digito;  
      n = n/10;  // Remove o último dígito do número
      i++;
    }
  }
  
  printf("Código BCD: ");
  for (int j = i - 1; j >= 0; j--) {
    printf("%04d ", bcd[j]);  // Exibe cada dígito como um número de 4 bits, atraves do formatador de saída %04d
  }
  printf("\n");
}
