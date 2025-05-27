#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/cadastro.h"
#include "../include/clearscreen.h"

/*
Função de criar Lista: aloca na memória um objeto do tipo Lista.
*/
Lista *criar_lista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->qtde = 0;
    return lista;
}

/*
Função de criar ELista: aloca na memória um objeto do tipo ELista.
*/
ELista *criar_Elista(Registro *registro) {
    ELista *elista = malloc(sizeof(ELista));
    elista->proximo = NULL;
    elista->dados = registro;
    return elista;
}

  // Função de cadastro.
void cadastrar(Lista *lista) {
 // Declaração de variáveis.
    char nome[100];
    char rg[20];
    int idade, dia, mes, ano;

    Registro *registro = malloc(sizeof(Registro));
    registro->entrada = malloc(sizeof(Data));

    clearScreen();
    getchar();
    printf("================================================== \n");
    printf("CADASTRAR NOVO PACIENTE \n");
    printf("================================================== \n");
    printf("Insira os dados de cadastro abaixo: \n");
    printf("\n Nome completo: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    printf(" Idade: ");
    scanf("%d", &idade);
    printf(" RG: ");
    scanf("%s", &rg);
    printf(" Data de entrada (Dia): ");
    scanf("%d", &dia);
    printf(" Data de entrada (Mês): ");
    scanf("%d", &mes);
    printf(" Data de entrada (Ano): ");
    scanf("%d", &ano);
    clearScreen();

    strcpy(registro->nome, nome);
    registro->idade = idade;
    strcpy(registro->rg, rg);
    registro->entrada->dia = dia;
    registro->entrada->mes = mes;
    registro->entrada->ano = ano;

    ELista *novoRegistro = criar_Elista(registro);
    novoRegistro->proximo = lista->primeiro;
    lista->primeiro = novoRegistro;
    lista->qtde++;
}

void mostrar_paciente(Lista *lista, char rg[20]) {
    ELista *atual = lista->primeiro;

    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        clearScreen();
        printf("\n ERRO: Paciente não encontrado.\n \n");
        sleep(2);
        clearScreen();
        return;

    } else {
        clearScreen();
        printf("==================================================");
        printf("\nINFORMAÇÕES DO PACIENTE\n");
        printf("==================================================");
        printf("\n NOME: %s", atual->dados->nome);
        printf("\n RG: %s", atual->dados->rg);
        printf("\n IDADE: %d", atual->dados->idade);
        printf("\n DATA DE ENTRADA: %d/%d/%d\n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
        printf("==================================================\n");
        printf("\n Pressione ENTER para voltar ao menu principal. ");
        getchar();
        getchar();
    }
}

int menuitem_cadastro(void) {
    int index;
    char rg[20];

    Lista *lista = criar_lista();
    do {
        printf("================================================== \n");
        printf("1. CADASTRAR\n");
        printf("================================================== \n");
        printf(" Digite o número da opção desejada abaixo: \n");
        printf(" 1. Cadastrar cliente\n");
        printf(" 2. Consultar paciente\n");
        printf(" 3. Consultar lista de pacientes\n");
        printf(" 4. Alterar dados de um cliente\n");
        printf(" 5. Remover cadastro de cliente\n");
        printf(" 6. Salvar\n");
        printf("\n Insira 0 para voltar ao menu principal.\n");
        printf("================================================== \n");
        printf("Digite aqui: ");
        scanf("%d", &index);

        switch(index) {
            case 1: {
                clearScreen();
                cadastrar(lista);
                clearScreen();
                break;
            }
            case 2: {
                clearScreen();
                printf("\n Insira o RG do paciente que deseja consultar: ");
                scanf("%s", rg);
                mostrar_paciente(lista, rg);
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
            case 0: {
                clearScreen();
                break;
            }
        }

    } while(index != 0);
    return 0;
}