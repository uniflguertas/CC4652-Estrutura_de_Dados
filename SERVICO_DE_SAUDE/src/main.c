#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/sobre.h"
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/pesquisa.h"
#include "../include/atendimento.h"
#include "../include/atendimento_prioritario.h"

// Aguarda o usuário pressionar ENTER para retornar ao menu principal
void voltarMenu(void) {
    printf("\n Pressione ENTER para voltar ao menu principal. ");
    getchar();
    getchar();
}

int main(void) {
    int index; // Variável para armazenar a opção do menu escolhida pelo usuário

    system("clear"); // Limpa o terminal

    Lista *lista = criar_lista();           // Cria a lista de pacientes
    carregar_lista(lista);                  // Carrega os dados salvos da lista
    Fila *fila = criar_fila();              // Cria a fila de atendimento
    Stack *stack = criar_stack();           // Cria a pilha para operações de desfazer

    do {
        // Exibe o menu principal
        printf("Seja bem-vindo ao Serviço de Atendimento de Saúde. \n");
        printf("O que gostaria de fazer hoje? \n");    
        printf("================================================== \n");
        printf("Digite o número da opção desejada abaixo: \n\n");
        printf("1. Cadastrar\n");
        printf("2. Atendimento\n");
        printf("3. Atendimento Prioritário\n");
        printf("4. Pesquisa\n");
        printf("5. Desfazer\n");
        printf("6. Salvar\n");
        printf("7. Sobre\n");
        printf("\nInsira 0 para sair.\n");
        printf("==================================================");
        printf("\nDigite aqui: ");
        scanf("%d", &index);

        // Trata a opção escolhida
        switch (index) {
            case 1: {
                system("clear");
                menuitem_cadastro(lista); // Abre submenu de cadastro
                system("clear");
                break;
            }
            case 2: {
                system("clear");
                menuitem_atendimento(fila, stack); // Submenu de atendimento comum
                system("clear");
                break;
            }
            case 3: {
                system("clear");
                menuitem_prioritario(); // Atendimento com prioridade (por idade)
                system("clear");
                break;
            }
            case 4: {
                system("clear");
                menuitem_pesquisa(); // Submenu de busca por informações
                system("clear");
                break;
            }
            case 5: {
                system("clear");
                int escolha;
                char *mensagem = mostrar_pop(stack); // Mostra a ação que pode ser desfeita
                printf("\nVocê deseja desfazer a ação abaixo?\n");
                printf("%s \n", mensagem);
                free(mensagem); // Libera memória da mensagem

                printf("Insira 1 para CONFIRMAR \n(Quaisquer outros valores serão tratados como NÃO)\n");
                printf("\nDigite aqui: ");
                scanf("%d", &escolha);

                switch(escolha) {
                    case 1: {
                        pop(stack, fila); // Desfaz a última ação realizada
                        break;
                    }
                    default: {
                        break;
                    }
                }
                system("clear");
                break;
            }
            case 6: {
                system("clear");
                salvar_lista(lista); // Salva os dados da lista em arquivo
                printf("\n Salvando... \n \n");
                sleep(1);
                system("clear");
                break;
            }
            case 7: {
                system("clear");
                sobre();        // Mostra informações sobre o sistema
                voltarMenu();   // Aguarda o ENTER para voltar ao menu
                system("clear");
                break;
            }
            case 0: {
                break; // Sai do programa
            }
            default: {
                system("clear");
                printf("\n404 - Not Found\n \n"); // Opção inválida
                sleep(1);
                system("clear");
                break;
            }
        };
    } while (index != 0); // Continua exibindo o menu até que o usuário escolha sair

    liberar_lista(lista); // Libera memória usada pela lista

    system("clear");
    printf("\n Encerrando... \n \n"); // Mensagem final de saída
    sleep(1);
    system("clear");

    return 0;
}
