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

    return efila;
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
    carregar_lista(lista);

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
    liberar_lista(lista);
}

int verificar_enfileiramento(Fila *fila, char rg[20]) {
    EFila *atual = fila->head;

    while(atual != NULL) {
        if(strcmp(atual->dados->rg, rg) == 0) {
            return 0;
        }
        atual = atual->proximo;
    }
    return 1;
}

void enfileirar(Fila *fila, char rg[20]) {
    Registro *registro = verifica_rg(rg);

    if(registro != NULL && verificar_enfileiramento(fila, rg) == 1) {
        EFila *novo = criar_Efila(registro);
        if (fila->qtde == 0) {
            fila->head = novo;
        } else {
            fila->tail->proximo = novo;
        }
        fila->tail = novo;
        fila->qtde++;
        clearScreen();
        printf("==================================================\n");
        printf("ENFILEIRAR PACIENTE\n");
        printf("==================================================\n");
        printf("\n %s enfileirado com sucesso! \n \n", novo->dados->nome);
        sleep(2);
        clearScreen();
    } else {
        clearScreen();
        printf("\n ERRO: RG inválido ou já enfileirado.");
        sleep(2);
        clearScreen();
    }
}

void desenfileirar(Fila *fila) {
    if (fila->qtde > 0) {
        EFila *efila = fila->head;
        fila->head = fila->head->proximo;

        if(fila->qtde == 1) {
            fila->tail = NULL;
        }
        fila->qtde--;

        clearScreen();
        printf("==================================================\n");
        printf("DESENFILEIRAR PACIENTE\n");
        printf("==================================================\n");
        printf("\n %s desenfileirado com sucesso! \n \n", efila->dados->nome);
        sleep(2);
        clearScreen();
        free(efila->dados->entrada);
        free(efila->dados);
        free(efila);
    } else {
        clearScreen();
        printf("\n ERRO: Não há pacientes para desenfileirar.");
        sleep(2);
        clearScreen();
    }
}

void mostrar_fila(Fila *fila) {
    EFila *atual = fila->head;
    printf("==================================================\n");
    printf("FILA DE PACIENTES\n");
    printf("==================================================\n");
    
    while(atual != NULL) {
        printf(" NOME: %s\n", atual->dados->nome);
        printf(" RG: %s\n", atual->dados->rg);
        printf(" DATA DE ENTRADA: %d/%d/%d\n \n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
        atual = atual->proximo;
    }

    printf("==================================================\n");
    printf("\n Pressione ENTER para voltar ao menu principal. ");
    getchar();
    getchar();
}

void liberar_fila(Fila *fila) {
    while (fila->qtde > 0) {  
        EFila *temp = fila->head;
        fila->head = fila->head->proximo;
        if (fila->qtde == 1) {
            fila->tail = NULL;
        }
        fila->qtde--;
        free(temp->dados->entrada);
        free(temp->dados);
        free(temp);
    }
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
                printf("\n Insira o RG do paciente que deseja enfileirar: ");
                scanf("%s", rg);
                enfileirar(fila, rg);
                clearScreen();
                break;
            }
            case 2: {
                clearScreen();
                printf("\n Insira o RG do paciente que deseja desenfileirar: ");
                scanf("%s", rg);
                desenfileirar(fila);
                clearScreen();
                break;
            }
            case 3: {
                clearScreen();
                mostrar_fila(fila);
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