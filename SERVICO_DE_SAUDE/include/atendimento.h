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

int menuitem_atendimento(void);
Registro* verifica_rg(char rg[20]);

#endif