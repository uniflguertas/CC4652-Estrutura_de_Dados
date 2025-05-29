#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H
#include "../include/cadastro.h"

typedef struct EFila {
    Registro *dados;
    struct EFila *proximo;
} EFila;

typedef struct {
    EFila *head;
    EFila *tail;
    int qtde;
} Fila;

typedef struct Celula {
    struct Celula *anterior;
    Registro *registro;
    struct Celula *proximo;
    int modo;
} Celula;

typedef struct {
    Celula *topo;
    int qtde;
}Stack;

Stack *criar_stack();
void push(Stack *stack, Registro *registro, int m);
void pop(Stack *stack, Fila *fila);
void desfazer_enfileirar(Fila *fila);
void desfazer_desenfileirar(Fila *fila, Registro *registro);
char* mostrar_pop(Stack *stack);
int menuitem_atendimento(Fila *fila, Stack *stack);
Registro* verifica_rg(char rg[20]);
void enfileirar(Fila *fila, char rg[20], Stack *stack);
void desenfileirar(Fila *fila, Stack *stack);
Fila *criar_fila();

#endif