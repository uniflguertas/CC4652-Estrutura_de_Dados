#ifndef PRIORIDADE_H
#define PRIORIDADE_H
#include "../include/cadastro.h"
#define MAX_PACIENTES 20

typedef struct {
    Registro *dados[MAX_PACIENTES];
    int qtde;
} HeapPrioridade;

int menuitem_prioritario(void);

void inserir_heap(HeapPrioridade *heap, char rg[20]);
void remover_heap(HeapPrioridade *heap);
void mostrar_heap(HeapPrioridade *heap);

#endif
