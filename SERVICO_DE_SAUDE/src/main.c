#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/sobre.h"
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/atendimento.h"
#include "../include/clearscreen.h"

/*
Função de retorno ao menu principal.
*/
void voltarMenu(void) {
    printf("\n Pressione ENTER para voltar ao menu principal. ");
    getchar();
    getchar();
}

/*
main(): imprime o menu e seleciona as opções.
*/
int main(void) {
 // index: seletor de opção.
    int index;

    clearScreen();
    Lista *lista = criar_lista();
    carregar_lista(lista);

 // do/while(): executa o print do menu enquanto index diferente de 8.
    do {
        printf("Seja bem-vindo ao Serviço de Atendimento de Saúde. \n");
        printf("O que gostaria de fazer hoje? \n");    
        printf("================================================== \n");
        printf("Digite o número da opção desejada abaixo: \n");
        printf("\n");
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

     // switch(): seleção de opção.
        switch (index) {
            case 1: {
                clearScreen();
                menuitem_cadastro(lista);
                clearScreen();
                break;
            }
            case 2: {
                clearScreen();
                menuitem_atendimento();
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
            case 4: {
                clearScreen();
                printf("\nOpção 4 selecionada.\n \n");
                sleep(1);
                clearScreen();
                break;
            }
            case 5: {
                clearScreen();
                printf("\nOpção 5 selecionada.\n \n");
                sleep(1);
                clearScreen();
                break;
            }
            case 6: {
                clearScreen();
                salvar_lista(lista);
                printf("\n Salvando... \n \n");
                sleep(1);
                clearScreen();
                break;
            }
            case 7: {
                clearScreen();
                sobre();
                voltarMenu();
                clearScreen();
                break;
            }
            case 0: {
                break;
            }
            default: {
                clearScreen();
                printf("\n404 - Not Found\n \n");
                sleep(1);
                clearScreen();
                break;
            }
        };
    }
    while (index != 0);
    liberar_lista(lista);
    
 // Print quando encerra o programa.
    clearScreen();
    printf("\n Encerrando... \n \n");
    sleep(1);
    clearScreen();
    
    return 0;
}