#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/atendimento.h"
#include "../include/clearscreen.h"
#include "../include/limpabuffer.h"

Celula *criar_celula (Registro *registro, int m) {
    Celula *celula = malloc(sizeof(Celula));
    celula->anterior = NULL;
    celula->proximo = NULL;

    celula->registro = malloc(sizeof(Registro));
    strcpy(celula->registro->nome, registro->nome);
    strcpy(celula->registro->rg, registro->rg);
    celula->registro->idade = registro->idade;

    celula->registro->entrada = malloc(sizeof(Data));
    celula->registro->entrada->dia = registro->entrada->dia;
    celula->registro->entrada->mes = registro->entrada->mes;
    celula->registro->entrada->ano = registro->entrada->ano;

    celula->modo = m;
    return celula;
}

EFila *criar_Efila(Registro *registro) {
    EFila *efila = malloc(sizeof(EFila));
    efila->proximo = NULL;
    efila->dados = registro;
}

Fila *criar_fila() {
    Fila *Fila = malloc(sizeof(Fila));
    Fila->head = NULL;
    Fila->tail = NULL;
    Fila->qtde = 0;

    return Fila;
}

Registro* verifica_rg(char rg[20]) {
    Lista *lista = malloc(sizeof(Lista));

    ELista *atual = lista->primeiro;
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        clearScreen();
        printf("\n ERRO: RG inválido.\n \n");
        sleep(2);
        clearScreen();
        return NULL;
    } else {
        return atual->dados;
    }
}

void enfileirar(Fila *fila, char rg[20]) {
    Registro *registro = malloc(sizeof(Registro));
}

int menuitem_atendimento(void) {
    int index;
    char rg[20];

    Fila *fila = criar_fila();

    do {
        printf("================================================== \n");
        printf("2. ATENDIMENTO\n");
        printf("================================================== \n");
        printf(" Digite o número da opção desejada abaixo: \n");
        printf(" 1. Enfileirar paciente\n");
        printf(" 2. Desenfileirar paciente\n");
        printf(" 3. Mostrar fila\n");
        printf("\n Insira 0 para voltar ao menu principal.\n");
        printf("================================================== \n");
        printf("Digite aqui: ");
        scanf("%d", &index);

        switch(index) {
            case 1: {
                clearScreen();
                printf("\nOpção 1 selecionada.\n \n");
                sleep(1);
                clearScreen();
                break;
            }
            case 2: {
                clearScreen();
                printf("\nOpção 2 selecionada.\n \n");
                sleep(1);
                clearScreen();
                break;
            }
            case 3: {
                clearScreen();
                printf("\nOpção 3 selecionada.\n \n");
                sleep(1);
                clearScreen();
                break;
            }
            case 0: {
                clearScreen();
                break;
            }
            default: {
                clearScreen();
                printf("\n404 - Not Found\n \n");
                sleep(1);
                clearScreen();
                break;
            }            
        }

    } while(index != 0);
    return 0;
}