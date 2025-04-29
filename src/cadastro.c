#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/cadastro.h"
#include "../include/clearscreen.h"

Lista *criar_lista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->qtde = 0;
    return lista;
}

ELista *criar_Elista(Registro *registro) {
    ELista *elista = malloc(sizeof(ELista));
    elista->proximo = NULL;
    elista->dados = registro;
    return elista;
}

int menuitem_cadastro(void) {
    int index;
    
    do {
        printf("================================================== \n");
        printf("Digite o número da opção desejada abaixo: \n");
        printf("1. Cadastrar cliente\n");
        printf("2. Consultar paciente\n");
        printf("3. Consultar lista de pacientes\n");
        printf("4. Alterar dados de um cliente\n");
        printf("5. Remover cadastro de cliente\n");
        printf("6. Salvar\n");
        printf("================================================== \n");
        printf("Insira 7 para voltar ao menu principal.\n");
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
                printf("\nOpção 6 selecionada.\n \n");
                sleep(1);
                clearScreen();
                break;
            }
            case 7: {
                clearScreen();
                break;
            }
        }

    } while(index != 7);
    return 0;
}
