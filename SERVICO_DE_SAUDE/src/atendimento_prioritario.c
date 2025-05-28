#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/atendimento.h"
#include "../include/clearscreen.h"
#include "../include/limpabuffer.h"
#include "../include/atendimento_prioritario.h"

void inserir_heap(HeapPrioridade *heap, char rg[20]) {
    Registro *registro = verifica_rg(rg);
    if (registro) {
        if (heap->qtde >= MAX_PACIENTES) return;

        int i = heap->qtde++;
        while (i > 0 && registro->idade > heap->dados[(i - 1) / 2]->idade) {
            heap->dados[i] = heap->dados[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        heap->dados[i] = registro;

        clearScreen();
        printf("==================================================\n");
        printf("ENFILEIRAR PACIENTE COM PRIORIDADE\n");
        printf("==================================================\n");
        printf("\n %s enfileirado com sucesso! \n \n", registro->nome);
    } else {
        clearScreen();
        printf("\n ERRO: RG inválido ou já enfileirado.\n");
    }

    sleep(2);
    clearScreen();
}

void remover_heap(HeapPrioridade *heap) {
    clearScreen();
    if (heap->qtde == 0) {
        printf("\n ERRO: Nenhum paciente na fila.\n \n");
        sleep(2);
        clearScreen();
        return;
    }

    Registro *removido = heap->dados[0];
    Registro *temp = heap->dados[--heap->qtde];

    int i = 0, maior;
    while ((2 * i + 1) < heap->qtde) {
        int esquerdo = 2 * i + 1;
        int direito = 2 * i + 2;

        maior = esquerdo;
        if (direito < heap->qtde && heap->dados[direito]->idade > heap->dados[esquerdo]->idade)
            maior = direito;

        if (temp->idade >= heap->dados[maior]->idade) break;

        heap->dados[i] = heap->dados[maior];
        i = maior;
    }
    heap->dados[i] = temp;

    clearScreen();
    printf("==================================================\n");
    printf("DESENFILEIRAR PACIENTE COM PRIORIDADE\n");
    printf("==================================================\n");
    printf("\n %s desenfileirado com sucesso! \n \n", removido->nome);
    sleep(2);
    clearScreen();
}

void mostrar_heap(HeapPrioridade *heap) {
    clearScreen();
    printf("==================================================\n");
    printf("FILA DE ATENDIMENTO PRIORITÁRIO (por idade)\n");
    printf("==================================================\n");
    
    if (heap->qtde == 0) {
        printf("\n Nenhum paciente encontrado.\n \n");
    } else {
        for (int i = 0; i < heap->qtde; i++) {
            printf(" NOME: %s\n", heap->dados[i]->nome);
            printf(" IDADE: %d\n", heap->dados[i]->idade);
            printf(" RG: %s\n", heap->dados[i]->rg);
            printf(" DATA DE ENTRADA: %d/%d/%d\n\n",
                heap->dados[i]->entrada->dia,
                heap->dados[i]->entrada->mes,
                heap->dados[i]->entrada->ano);
        }
    }
    printf("==================================================\n");
    printf("\n Pressione ENTER para voltar ao menu principal. ");
    getchar();
    getchar();
    clearScreen();
}

int menuitem_prioritario(void) {
    int index;
    char rg[20];
    HeapPrioridade heap;
    heap.qtde = 0;

    do {
        printf("================================================== \n");
        printf("ATENDIMENTO PRIORITÁRIO\n");
        printf("================================================== \n");
        printf(" 1. Enfileirar paciente\n");
        printf(" 2. Desenfileirar paciente\n");
        printf(" 3. Mostrar fila\n");
        printf(" \n Insira 0 para voltar ao menu principal.\n");
        printf("================================================== \n");
        printf("Digite aqui: ");
        scanf("%d", &index);

        switch(index) {
            case 1:
                clearScreen();
                printf("\n Insira o RG do paciente que deseja enfileirar com prioridade: ");
                scanf("%s", rg);
                inserir_heap(&heap, rg);
                break;
            case 2:
                remover_heap(&heap);
                break;
            case 3:
                mostrar_heap(&heap);
                break;
            case 0:
                clearScreen();
                break;
            default:
                clearScreen();
                printf("\n404 - Not Found\n \n");
                sleep(1);
                clearScreen();
                break;
        }
    } while(index != 0);

    return 0;
}
