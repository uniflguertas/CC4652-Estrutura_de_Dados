#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/atendimento.h"
#include "../include/limpabuffer.h"
#include "../include/atendimento_prioritario.h"

void inserir_heap(HeapPrioridade *heap, char rg[20]) {
    Registro *registro = verifica_rg(rg);  // Verifica se o RG é válido e retorna o registro do paciente
    if (registro) {  // Se registro existe (RG válido)
        if (heap->qtde >= MAX_PACIENTES) return;  // Se a fila estiver cheia, não insere

        int i = heap->qtde++;  // Posição para inserir o novo paciente (fim da heap)
        // "Sobe" o paciente na heap enquanto sua idade for maior que a do pai (heap máxima por idade)
        while (i > 0 && registro->idade > heap->dados[(i - 1) / 2]->idade) {
            heap->dados[i] = heap->dados[(i - 1) / 2];  // Move o pai para baixo
            i = (i - 1) / 2;  // Atualiza índice para o pai
        }
        heap->dados[i] = registro;  // Insere o novo paciente na posição correta

        system("clear");  // Limpa a tela
        printf("==================================================\n");
        printf("ENFILEIRAR PACIENTE COM PRIORIDADE\n");
        printf("==================================================\n");
        printf("\n %s enfileirado com sucesso! \n \n", registro->nome);  // Confirma inserção
    } else {
        system("clear");
        printf("\n ERRO: RG inválido ou já enfileirado.\n");  // RG inválido ou paciente já na fila
    }

    sleep(2);  // Pausa para mostrar mensagem
    system("clear");  // Limpa tela após a pausa
}

void remover_heap(HeapPrioridade *heap) {
    system("clear");
    if (heap->qtde == 0) {  // Verifica se a fila está vazia
        printf("\n ERRO: Nenhum paciente na fila.\n \n");
        sleep(2);
        system("clear");
        return;
    }

    Registro *removido = heap->dados[0];  // Guarda o paciente do topo (maior idade) para mostrar depois
    Registro *temp = heap->dados[--heap->qtde];  // Pega o último paciente da heap para reposicionar

    int i = 0, maior;
    // "Desce" o paciente temporário para manter a propriedade da heap máxima
    while ((2 * i + 1) < heap->qtde) {
        int esquerdo = 2 * i + 1;  // Filho esquerdo
        int direito = 2 * i + 2;   // Filho direito

        maior = esquerdo;  // Assume que o maior é o filho esquerdo
        if (direito < heap->qtde && heap->dados[direito]->idade > heap->dados[esquerdo]->idade)
            maior = direito;  // Se o filho direito for maior, atualiza

        if (temp->idade >= heap->dados[maior]->idade) break;  // Se temp é maior que os filhos, para o loop

        heap->dados[i] = heap->dados[maior];  // Move o maior filho para cima
        i = maior;  // Atualiza índice para continuar descendo
    }
    heap->dados[i] = temp;  // Insere temp na posição correta

    system("clear");
    printf("==================================================\n");
    printf("DESENFILEIRAR PACIENTE COM PRIORIDADE\n");
    printf("==================================================\n");
    printf("\n %s desenfileirado com sucesso! \n \n", removido->nome);  // Mostra paciente removido
    sleep(2);
    system("clear");
}

void mostrar_heap(HeapPrioridade *heap) {
    system("clear");
    printf("==================================================\n");
    printf("FILA DE ATENDIMENTO PRIORITÁRIO (por idade)\n");
    printf("==================================================\n");
    
    if (heap->qtde == 0) {
        printf("\n Nenhum paciente encontrado.\n \n");  // Mensagem se fila vazia
    } else {
        // Percorre a heap e imprime os dados de cada paciente
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
    getchar();  // Espera Enter
    getchar();  // Captura o Enter (para evitar bug no buffer)
    system("clear");
}

int menuitem_prioritario(void) {
    int index;
    char rg[20];
    HeapPrioridade heap;
    heap.qtde = 0;  // Inicializa a heap vazia

    do {
        // Mostra o menu para o usuário
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
                system("clear");
                printf("\n Insira o RG do paciente que deseja enfileirar com prioridade: ");
                scanf("%s", rg);
                inserir_heap(&heap, rg);  // Chama função para inserir paciente na heap
                break;
            case 2:
                remover_heap(&heap);  // Chama função para remover paciente da heap
                break;
            case 3:
                mostrar_heap(&heap);  // Exibe os pacientes na fila
                break;
            case 0:
                system("clear");  // Sai do menu limpando tela
                break;
            default:
                system("clear");
                printf("\n404 - Not Found\n \n");  // Entrada inválida
                sleep(1);
                system("clear");
                break;
        }
    } while(index != 0);  // Repete até o usuário escolher sair

    return 0;
}
