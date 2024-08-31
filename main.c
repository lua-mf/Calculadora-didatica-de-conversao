/*
 * Calculadora Didática de Conversão
 * Autor: Luana Costa Lima Maynard de Arruda Falcão
 * Data de criação: [30/08/2024]
 * Última atualização: [30/08/2024 às 23:24]
 * GitHub: https://github.com/lua-mf/Calculadora-didatica-de-conversao
 * Descrição: Este programa realiza conversões de base 10 para outras bases e representações numéricas, mostrando os passos detalhados na tela.
 *
 * Revisões/Atualizações:
 * - [30/08/2024 às 18:05]: Implementação inicial.
 * - [30/08/2024 às 18:10]: Escrita do README.
 * - [30/08/2024 às 18:36]: Menu e criação das primeiras funções
 * - [30/08/2024 às 19:03]: correção do Menu
 * - [30/08/2024 às 22:16]: adição da funçãod de a2
 * - [30/08/2024 às 22:16]: adição das funções de converter_para_decimal, imprimir_float e imprimir_double
 */
#include <stdio.h>
#include <math.h>
#include <stdint.h>

typedef struct Node{
  char num;
  struct Node *prox;
}Node;

void add(Node **head, char n);
void imprimir(Node *head);
void conversaoBase(int n, int base, Node *head);
void BCD(int n);
void A216(int n);
void imprimir_float(float n);
void imprimir_double(double n);
int converter_para_decimal(float n);
  
int main(void) {
  int resposta, nint, base;
  float nfloat;
  Node *head = NULL;
  
  do{
    printf("\n==================== Cáculadora Didática de Conversão ======================\n\n");
    printf("1 - Conversão de decimal para binario\n");
    printf("2 - Conversão de decimal para octal\n");
    printf("3 - Conversão de decimal para hexadecimal\n");
    printf("4 - Conversão de decimal para o côdigo BCD\n");
    printf("5 - Conversão de decimal para base com sinal com 16 bits (complemento a 2)\n");
    printf("6 - Conversão de real em decimal para float e double\n");
    printf("7 - Sair \n");

    printf("\nDigite a opção que deseja: ");      
    scanf(" %d", &resposta);
  
    if(resposta==1 || resposta==2 || resposta==3){
      printf("\nDigite um número inteiro decimal: ");
      scanf("%d", &nint);
      if(resposta==1){
        base = 2;
      }else if(resposta==2){
        base = 8;
      }else if(resposta==3){
        base = 16;
      }
      conversaoBase(nint, base, head);
      
    }else if(resposta==4){
      //BCD
      printf("\nDigite um número inteiro decimal: ");
      scanf("%d", &nint);
      BCD(nint);
    }else if(resposta==5){
      // base 10 para base com sinal com 16 bits
      printf("\nDigite um número inteiro decimal: ");
      scanf("%d", &nint);
      A216(nint);
    }else if(resposta==6){
      printf("\nDigite um número real: ");
      scanf("%f", &nfloat);
      imprimir_float(nfloat);
      imprimir_double(nfloat);
    }else{
      printf("\nPor favor digite o número correspondente a uma das opções!");
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
      add(&head, '0' + resto);//transforma o decimal em char
    }else if(base==16){
      if (resto < 10){
        add(&head, '0' + resto);//Para 0-9
      }else{
        add(&head, 'A' + (resto - 10));//Para A-F
      }
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

void A216(int n){
  int A216[16], sinal = 0;
  
  if(n < 0){
    sinal = 1;
    n = -n; // torna o numero positivo, invertendo o sinal de n
  }
  printf("\nPasso a Passo:");
  // Converte para a base 2
  for(int i = 15; i >= 0; i--){
    A216[i] = n % 2;
    n = n/2;
  }
  // imprimi o binário do numero
  printf("\n1) Em base 2: ");
  for(int i = 0; i < 16; i++){
    if(i > 0 && i % 4 == 0){
      printf(" "); // imprimi 1 espaço entre 4 bits
    } 
    printf("%d", A216[i]);
  }
  printf("\n");

  if(sinal==1){
  // Complemento a 1(inversao dos bits)
  printf("\n2) Complemento a 1 (inversao dos bits): ");
  for(int i = 0; i < 16; i++){
    A216[i] = !A216[i];
  }

  // Mostrar o complemento a 1
  for(int i = 0; i < 16; i++){
    if(i > 0 && i % 4 == 0){
      printf(" "); 
    } 
    printf("%d", A216[i]);
  }
  printf("\n");

  // Soma de  + 1 ao complemento a 1
  printf("\n3) Soma de 1 ao complemento a 1: ");
  for(int i = 0; i < 16; i++){
    if(i > 0 && i % 4 == 0){
      printf(" "); 
    } 
    printf("%d", A216[i]);
  }
  printf(" + 1 = ");
  for(int i = 15; i >= 0; i--){
    if (A216[i] == 0) {
      A216[i] = 1;
      break;
    } else {
      A216[i] = 0;
    }
  }

  // Imprime o resultado do complemento a 2
  for(int i = 0; i < 16; i++){
    if(i > 0 && i % 4 == 0){
      printf(" "); 
    } 
      printf("%d", A216[i]);
    }
    printf("\n");
  }

  printf("\n4) Em complemento a 2 com 16 bits: ");
  for(int i = 0; i < 16; i++){
    if(i > 0 && i % 4 == 0){
      printf(" "); 
    } 
    printf("%d", A216[i]);
  }
  printf("\n");
}

int converter_para_decimal(float n){
  int decimal = (int)n;
  return decimal;
}
void imprimir_float(float n) {
    uint32_t bits = *(uint32_t *)&n;// transforma o n em um inteiro de 32 bits (uint32_t), para poder acessar os bits diretamente

    printf("\nFloat:\n\n");
    printf(" - número em decimal: %d\n", converter_para_decimal(n));
    printf(" - sinal: %d\n", (bits >> 31) & 1); // O símbolo ">>" desloca bits para a direita
    printf(" - expoente: %d\n", (bits >> 23) & 0xFF); 
    printf(" - expoente com viés: %d\n", ((bits >> 23) & 0xFF) - 127); 
    printf(" - fração: 0x%06x\n", bits & 0x7FFFFF); 
}

void imprimir_double(double n) {
    uint64_t bits = *(uint64_t *)&n;// transforma o n em um inteiro de 64 bits (uint32_t), para poder acessar os bits diretamente

    printf("\nDouble:\n\n");
    printf(" - número em decimal: %d\n", converter_para_decimal(n));
    printf(" - sinal: %d\n", (bits >> 63) & 1); // é deslocado 63 posições para a direita, assim pegando o bit de sinal
    printf(" - expoente: %d\n", (bits >> 52) & 0x7FF); 
    printf(" - expoente com viés: %d\n", ((bits >> 52) & 0x7FF) - 1023); 
    printf(" - fração: 0x%013lx\n", bits & 0xFFFFFFFFFFFFF); 
}
