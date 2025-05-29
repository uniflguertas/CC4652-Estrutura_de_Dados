#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/pesquisa.h"

// Percorre a árvore em ordem simétrica e imprime os registros de acordo com o modo escolhido
void in_ordem(Vertice *raiz, int modo) {
    if (raiz != NULL) {
        in_ordem(raiz->esquerdo, modo); // Visita a subárvore esquerda

        // Imprime os dados de acordo com o modo (campo de ordenação)
        switch (modo) {
            case 1: // Ordenação por dia
                printf(" DIA: %d, ", raiz->registro->entrada->dia);
                printf(" MÊS: %d, ", raiz->registro->entrada->mes);
                printf(" ANO: %d, ", raiz->registro->entrada->ano);
                printf(" IDADE: %d, ", raiz->registro->idade);
                printf(" RG: %s, ", raiz->registro->rg);
                printf(" NOME: %s \n", raiz->registro->nome);
                break;
            case 2: // Ordenação por mês
                printf(" MÊS: %d, ", raiz->registro->entrada->mes);
                printf(" DIA: %d, ", raiz->registro->entrada->dia);
                printf(" ANO: %d, ", raiz->registro->entrada->ano);
                printf(" IDADE: %d, ", raiz->registro->idade);
                printf(" RG: %s, ", raiz->registro->rg);
                printf(" NOME: %s\n", raiz->registro->nome);
                break;
            case 3: // Ordenação por ano
                printf(" ANO: %d, ", raiz->registro->entrada->ano);
                printf(" MÊS: %d, ", raiz->registro->entrada->mes);
                printf(" DIA: %d, ", raiz->registro->entrada->dia);
                printf(" IDADE: %d, ", raiz->registro->idade);
                printf(" RG: %s, ", raiz->registro->rg);
                printf(" NOME: %s\n", raiz->registro->nome);
                break;
            case 4: // Ordenação por idade
                printf(" IDADE: %d, ", raiz->registro->idade);
                printf(" ANO: %d, ", raiz->registro->entrada->ano);
                printf(" MÊS: %d, ", raiz->registro->entrada->mes);
                printf(" DIA: %d, ", raiz->registro->entrada->dia);
                printf(" RG: %s, ", raiz->registro->rg);
                printf(" NOME: %s\n", raiz->registro->nome);
                break;
            default:
                return;
        }

        in_ordem(raiz->direito, modo); // Visita a subárvore direita
    }
}

// Cria um novo vértice a partir de um registro (cópia profunda)
Vertice* criar_vertice(Registro *registro) {
    Vertice* vertice = malloc(sizeof(Vertice));
    vertice->registro = malloc(sizeof(Registro));
    vertice->registro->entrada = malloc(sizeof(Data));

    // Copia os campos do registro
    vertice->registro->idade = registro->idade;
    strcpy(vertice->registro->nome, registro->nome);
    strcpy(vertice->registro->rg, registro->rg);
    vertice->registro->entrada->dia = registro->entrada->dia;
    vertice->registro->entrada->mes = registro->entrada->mes;
    vertice->registro->entrada->ano = registro->entrada->ano;

    // Inicializa ponteiros
    vertice->direito = NULL;
    vertice->esquerdo = NULL;
    vertice->pai = NULL;

    return vertice;
}

// Cria uma árvore binária de busca vazia
Arvore *criar_arvore(){
    Arvore* arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->qtde = 0;
    return arvore;
}

// Insere um registro na árvore comparando pelo dia de entrada
void inserir_por_dia(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    // Busca posição correta na árvore
    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->dia < atual->registro->entrada->dia)
            atual = atual->esquerdo;
        else
            atual = atual->direito;
    }

    // Insere o novo vértice
    novo->pai = pai;
    if (pai == NULL)
        arvore->raiz = novo;
    else if (registro->entrada->dia < pai->registro->entrada->dia)
        pai->esquerdo = novo;
    else
        pai->direito = novo;

    arvore->qtde++;
}

// Insere um registro na árvore comparando pelo mês
void inserir_por_mes(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->mes < atual->registro->entrada->mes)
            atual = atual->esquerdo;
        else
            atual = atual->direito;
    }

    novo->pai = pai;
    if (pai == NULL)
        arvore->raiz = novo;
    else if (registro->entrada->mes < pai->registro->entrada->mes)
        pai->esquerdo = novo;
    else
        pai->direito = novo;

    arvore->qtde++;
}

// Insere um registro na árvore comparando pelo ano
void inserir_por_ano(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->ano < atual->registro->entrada->ano)
            atual = atual->esquerdo;
        else
            atual = atual->direito;
    }

    novo->pai = pai;
    if (pai == NULL)
        arvore->raiz = novo;
    else if (registro->entrada->ano < pai->registro->entrada->ano)
        pai->esquerdo = novo;
    else
        pai->direito = novo;

    arvore->qtde++;
}

// Insere um registro na árvore comparando pela idade
void inserir_por_idade(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->idade < atual->registro->idade)
            atual = atual->esquerdo;
        else
            atual = atual->direito;
    }

    novo->pai = pai;
    if (pai == NULL)
        arvore->raiz = novo;
    else if (registro->idade < pai->registro->idade)
        pai->esquerdo = novo;
    else
        pai->direito = novo;

    arvore->qtde++;
}

// Percorre todos os registros da lista e insere na árvore de acordo com o modo (campo de ordenação)
void inserir(Arvore *arvore, int modo) {
    Lista *lista = malloc(sizeof(Lista));
    carregar_lista(lista); // Carrega os dados do arquivo para a lista

    ELista *elista = lista->primeiro;
    while(elista != NULL) {
        Registro *registro = elista->dados;
        switch (modo) {
            case 1:
                inserir_por_dia(arvore, registro);
                break;
            case 2:
                inserir_por_mes(arvore, registro);
                break;
            case 3:
                inserir_por_ano(arvore, registro);
                break;
            case 4:
                inserir_por_idade(arvore, registro);
                break;
            default:
                system("clear");
                printf("\n ERRO: Modo de inserção inválido.\n \n");
                sleep(1);
                system("clear");
                break;
        }
        elista = elista->proximo;
    }
    free(lista);
}

// Libera a memória de todos os vértices da árvore
void liberar_arvore(Vertice* vertice) {
    if (vertice != NULL) {
        liberar_arvore(vertice->esquerdo);
        liberar_arvore(vertice->direito);
        free(vertice);
    }
}

// Exibe o menu de pesquisa e permite exibir registros ordenados por diferentes campos
void menuitem_pesquisa() {
    int index;

    do {
        Arvore *arvore = criar_arvore(); // Cria uma nova árvore vazia

        // Exibe o menu de opções de pesquisa
        printf("================================================== \n");
        printf("4. PESQUISA\n");
        printf("================================================== \n");
        printf(" Digite o número da opção desejada abaixo: \n");
        printf(" 1. Mostrar registros ordenados por ano de registro\n");
        printf(" 2. Mostrar registros ordenados por mês de registro\n");
        printf(" 3. Mostrar registros ordenados por dia de registro\n");
        printf(" 4. Mostrar registros ordenados por idade do paciente\n");
        printf("\n Insira 0 para voltar ao menu principal.\n");
        printf("================================================== \n");
        printf("Digite aqui: ");
        scanf("%d", &index);

        if (index >= 1 && index <= 4) {
            system("clear");
            printf("============================================================================= \n");
            printf("PESQUISA\n");
            printf("============================================================================= \n");

            inserir(arvore, index);              // Insere os registros na árvore conforme o critério
            in_ordem(arvore->raiz, index);       // Imprime os registros ordenados
            liberar_arvore(arvore->raiz);        // Libera memória da árvore

            printf("=============================================================================\n");
            printf("\n Pressione ENTER para voltar ao menu principal. ");
            getchar();
            getchar();
            system("clear");
        } else if (index == 0){
            break; // Retorna ao menu principal
        } else {
            system("clear");
            printf("\n ERRO: Opção inválida. \n \n");
            sleep(1);
            system("clear");
        }

    } while (index != 0);
}
