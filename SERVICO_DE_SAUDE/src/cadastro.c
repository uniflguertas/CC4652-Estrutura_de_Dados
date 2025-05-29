#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/limpabuffer.h"

Lista *criar_lista() {
    // Aloca memória para a lista, inicializa ponteiro e contador
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->qtde = 0;
    return lista;
}

ELista *criar_Elista(Registro *registro) {
    // Cria um elemento da lista encadeada com os dados recebidos
    ELista *elista = malloc(sizeof(ELista));
    elista->proximo = NULL;
    elista->dados = registro;
    return elista;
}

void cadastrar(Lista *lista) {
    // Variáveis temporárias para entrada dos dados
    char nome[100], rg[20];
    int idade, dia, mes, ano;

    // Aloca registro e subestrutura data
    Registro *registro = malloc(sizeof(Registro));
    registro->entrada = malloc(sizeof(Data));

    system("clear"); // Limpa a tela
    getchar(); // Limpa buffer de entrada pendente

    // Leitura dos dados do paciente
    printf("================================================== \n");
    printf("CADASTRAR NOVO PACIENTE \n");
    printf("================================================== \n");
    printf("Insira os dados de cadastro abaixo: \n");
    printf("\n Nome completo: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0; // Remove '\n' do fgets
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
    system("clear");

    // Copia dados para a struct registro
    strcpy(registro->nome, nome);
    registro->idade = idade;
    strcpy(registro->rg, rg);
    registro->entrada->dia = dia;
    registro->entrada->mes = mes;
    registro->entrada->ano = ano;

    // Cria elemento e insere no início da lista
    ELista *novoRegistro = criar_Elista(registro);
    novoRegistro->proximo = lista->primeiro;
    lista->primeiro = novoRegistro;
    lista->qtde++;
}

void consultar_paciente(Lista *lista, char rg[20]) {
    ELista *atual = lista->primeiro;

    // Percorre lista procurando RG correspondente
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo; 
    }

    if (atual == NULL) { // RG não encontrado
        system("clear");
        printf("\n ERRO: RG inválido.\n \n");
        sleep(2);
        system("clear");
        return;
    } else { // Exibe dados do paciente
        system("clear");
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

void mostrar_lista(Lista *lista) {
    int contador = 0;
    ELista *atual = lista->primeiro;

    // Exibe cabeçalho da lista
    printf("==================================================\n");
    printf("LISTA DE PACIENTES\n");
    printf("==================================================\n");

    // Se lista vazia, avisa
    if(atual == NULL && contador == 0) {
        printf("\n Nenhum paciente encontrado.\n \n");
    } else {
        // Percorre e imprime os dados dos pacientes
        while (atual != NULL) {
            printf(" NOME: %s\n", atual->dados->nome);
            printf(" DATA DE ENTRADA: %d/%d/%d\n \n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
            atual = atual->proximo;
            contador++;
        };
    }
    printf("==================================================\n");
    printf("\n Pressione ENTER para voltar ao menu principal. ");
    getchar();
    getchar();
}

void atualizar_paciente(Lista *lista, char rg[20]) {
    int index;
    ELista *atual = lista->primeiro;

    // Busca paciente pelo RG
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }

    if (atual == NULL) { // RG inválido
        system("clear");
        printf("\n ERRO: RG inválido \n \n");
        sleep(2);
        system("clear");
        return;
    }

    do {
        system("clear");

        // Menu de atualização das informações do paciente
        printf("==================================================\n");
        printf("ATUALIZAR INFORMAÇÕES DO PACIENTE\n");
        printf("==================================================\n");
        printf("Digite o número da opção desejada abaixo:\n");
        printf("1. Nome\n");
        printf("2. RG\n");
        printf("3. Idade\n");
        printf("4. Data da entrada\n");
        printf("\n \n Insira 0 para voltar ao menu.\n");
        printf("==================================================\n");
        printf("Digite aqui: ");
        scanf("%d", &index);

        switch (index) {
            case 1: {
                // Atualiza nome
                char novo_nome[100];
                system("clear");
                printf("==================================================\n");
                printf("ATUALIZAR INFORMAÇÕES DO PACIENTE\n");
                printf("==================================================\n");
                printf("1. Nome\n");
                printf("\n Insira o novo nome: ");
                limpar_buffer();
                fgets(novo_nome, sizeof(novo_nome), stdin);
                novo_nome[strcspn(novo_nome, "\n")] = 0;
                strcpy(atual->dados->nome, novo_nome);
                break;
            }

            case 2: {
                // Atualiza RG
                char novo_rg[20];
                system("clear");
                printf("==================================================\n");
                printf("ATUALIZAR INFORMAÇÕES DO PACIENTE\n");
                printf("==================================================\n");
                printf("2. RG\n");
                printf("\n Insira o novo RG: ");
                scanf("%s", novo_rg);
                strcpy(atual->dados->rg, novo_rg);
                break;
            }

            case 3: {
                // Atualiza idade
                int nova_idade;
                system("clear");
                printf("==================================================\n");
                printf("ATUALIZAR INFORMAÇÕES DO PACIENTE\n");
                printf("==================================================\n");
                printf("3. Idade\n");
                printf("\n Insira a nova idade: ");
                scanf("%d", &nova_idade);
                atual->dados->idade = nova_idade;
                break;
            }

            case 4: {
                // Atualiza data de entrada
                int novo_dia, novo_mes, novo_ano;
                system("clear");
                printf("==================================================\n");
                printf("ATUALIZAR INFORMAÇÕES DO PACIENTE\n");
                printf("==================================================\n");
                printf("4. Data da entrada\n");
                printf("\n Insira a nova data(dia): ");
                scanf("%d", &novo_dia);
                atual->dados->entrada->dia = novo_dia;
                printf("\n Insira a nova data(mês): ");
                scanf("%d", &novo_mes);
                atual->dados->entrada->mes = novo_mes;
                printf("\n Insira a nova data(ano): ");
                scanf("%d", &novo_ano);
                atual->dados->entrada->ano = novo_ano;
                break;
            }
        }
    } while (index != 0); // Continua até o usuário escolher voltar
}

void remover_paciente(Lista *lista, char rg[20]) {
    ELista *atual = lista->primeiro;
    ELista *anterior = NULL;

    // Busca elemento com o RG especificado
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) { // RG não encontrado
        system("clear");
        printf("\n ERRO: RG inválido \n \n");
        sleep(2);
        system("clear");
        return;
    }

    // Remove da lista ajustando ponteiros
    if (anterior == NULL) {
        lista->primeiro = atual->proximo; // Se for o primeiro da lista
    } else {
        anterior->proximo = atual->proximo;
    }

    system("clear");
    printf("==================================================\n");
    printf("REMOVER PACIENTE\n");
    printf("==================================================\n");
    printf("\n %s removido com sucesso! \n \n", atual->dados->nome);
    sleep(2);
    system("clear");

    // Libera memória e decrementa contador
    free(atual);
    lista->qtde--;
}

void liberar_lista(Lista *lista){
    ELista *atual = lista->primeiro;

    // Percorre toda lista liberando memória de cada nó e seus dados
    while(lista->qtde > 0){
        ELista *temp = atual;
        atual = atual->proximo;
        lista->qtde--;
        free(temp->dados->entrada);
        free(temp->dados);
        free(temp);
    }
    free(lista); // Libera a estrutura da lista
}

int menuitem_cadastro(Lista *lista) {
    int index;
    char rg[20];

    do {
        // Exibe menu principal para cadastro/consulta/atualização/remover
        printf("================================================== \n");
        printf("1. CADASTRAR\n");
        printf("================================================== \n");
        printf(" Digite o número da opção desejada abaixo: \n");
        printf(" 1. Cadastrar cliente\n");
        printf(" 2. Consultar paciente\n");
        printf(" 3. Consultar lista de pacientes\n");
        printf(" 4. Alterar dados de um cliente\n");
        printf(" 5. Remover cadastro de cliente\n");
        printf("\n Insira 0 para voltar ao menu principal.\n");
        printf("================================================== \n");
        printf("Digite aqui: ");
        scanf("%d", &index);

        switch(index) {
            case 1: // Chama função cadastrar
                system("clear");
                cadastrar(lista);
                system("clear");
                break;
            case 2: // Consulta paciente por RG
                system("clear");
                printf("\n Insira o RG do paciente que deseja consultar: ");
                scanf("%s", rg);
                consultar_paciente(lista, rg);
                system("clear");
                break;
            case 3: // Mostra lista completa
                system("clear");
                mostrar_lista(lista);
                system("clear");
                break;
            case 4: // Atualiza dados do paciente
                system("clear");
                printf("\n Insira o RG do paciente que deseja consultar: ");
                scanf("%s", rg);
                atualizar_paciente(lista, rg);
                system("clear");
                break;
            case 5: // Remove paciente da lista
                system("clear");
                printf("\n Insira o RG do paciente que deseja remover: ");
                scanf("%s", rg);
                remover_paciente(lista, rg);
                system("clear");
                break;
            case 0: // Sai do menu
                system("clear");
                break;
            default: // Opção inválida
                system("clear");
                printf("\n404 - Not Found\n \n");
                sleep(1);
                system("clear");
                break;
        }

    } while(index != 0); // Repetição do menu até usuário escolher sair
    return 0;
}