#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/pesquisa.h"
#include "../include/clearscreen.h"

void in_ordem(Vertice *raiz, int modo) {
    if (raiz != NULL) {
        in_ordem(raiz->esquerdo, modo);
        switch (modo) {
            case 1:
                printf(" DIA: %d, ", raiz->registro->entrada->dia);
                printf(" MÊS: %d, ", raiz->registro->entrada->mes);
                printf(" ANO: %d, ", raiz->registro->entrada->ano);
                printf(" IDADE: %d, ", raiz->registro->idade);
                printf(" RG: %s, ", raiz->registro->rg);
                printf(" NOME: %s \n", raiz->registro->nome);
                break;
            case 2:
                printf(" MÊS: %d, ", raiz->registro->entrada->mes);
                printf(" DIA: %d, ", raiz->registro->entrada->dia);
                printf(" ANO: %d, ", raiz->registro->entrada->ano);
                printf(" IDADE: %d, ", raiz->registro->idade);
                printf(" RG: %s, ", raiz->registro->rg);
                printf(" NOME: %s\n", raiz->registro->nome);
                break;
            case 3:
                printf(" ANO: %d, ", raiz->registro->entrada->ano);
                printf(" MÊS: %d, ", raiz->registro->entrada->mes);
                printf(" DIA: %d, ", raiz->registro->entrada->dia);
                printf(" IDADE: %d, ", raiz->registro->idade);
                printf(" RG: %s, ", raiz->registro->rg);
                printf(" NOME: %s\n", raiz->registro->nome);
                break;
            case 4:
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
        
        in_ordem(raiz->direito, modo);
    }
}

Vertice* criar_vertice(Registro *registro) {
    Vertice* vertice = malloc(sizeof(Vertice));
    vertice->registro = malloc(sizeof(Registro));
    vertice->registro->entrada = malloc(sizeof(Data));
    vertice->registro->idade = registro->idade;
    strcpy(vertice->registro->nome, registro->nome);
    strcpy(vertice->registro->rg, registro->rg);
    vertice->registro->entrada->dia = registro->entrada->dia;
    vertice->registro->entrada->mes = registro->entrada->mes;
    vertice->registro->entrada->ano = registro->entrada->ano;
    vertice->direito = NULL;
    vertice->esquerdo = NULL;
    vertice->pai = NULL;
    return vertice;
}

Arvore *criar_arvore(){
	Arvore* arvore = malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	arvore->qtde = 0;

	return arvore;
}

void inserir_por_dia(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->dia < atual->registro->entrada->dia) {
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }

    novo->pai = pai;
    if (pai == NULL) { 
        arvore->raiz = novo;
    } else if (registro->entrada->dia < pai->registro->entrada->dia) {
        pai->esquerdo = novo;
    } else {
        pai->direito = novo;
    }
    arvore->qtde++;
}

void inserir_por_mes(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->mes < atual->registro->entrada->mes) {
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }

    novo->pai = pai;
    if (pai == NULL) {
        arvore->raiz = novo;
    } else if (registro->entrada->mes < pai->registro->entrada->mes) {
        pai->esquerdo = novo;
    } else {
        pai->direito = novo;
    }
    arvore->qtde++;
}

void inserir_por_ano(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->ano < atual->registro->entrada->ano) {
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }

    novo->pai = pai;
    if (pai == NULL) {
        arvore->raiz = novo;
    } else if (registro->entrada->ano < pai->registro->entrada->ano) {
        pai->esquerdo = novo;
    } else {
        pai->direito = novo;
    }
    arvore->qtde++;
}

void inserir_por_idade(Arvore *arvore, Registro *registro) {
    Vertice *novo = criar_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;
    while (atual != NULL) {
        pai = atual;
        if (registro->idade < atual->registro->idade) {
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }
    novo->pai = pai;
    if (pai == NULL) {
        arvore->raiz = novo;
    } else if (registro->idade < pai->registro->idade) {
        pai->esquerdo = novo;
    } else {    
        pai->direito = novo;
    }
    arvore->qtde++;
}

void inserir(Arvore *arvore, int modo) {
    Lista *lista = malloc(sizeof(Lista));
    carregar_lista(lista);

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
                clearScreen();
                printf("\n ERRO: Modo de inserção inválido.\n \n");
                sleep(1);
                clearScreen();
                break;
        }

        elista = elista->proximo;
    }
    free(lista);
}

void liberar_arvore(Vertice* vertice) {
    if (vertice != NULL) {
        liberar_arvore(vertice->esquerdo);
        liberar_arvore(vertice->direito);
        free(vertice);
    }
}

void menuitem_pesquisa() {
    int index;

    do {
        Arvore *arvore = criar_arvore();
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
            clearScreen();
            printf("============================================================================= \n");
            printf("PESQUISA\n");
            printf("============================================================================= \n");
            inserir(arvore, index);
            in_ordem(arvore->raiz, index);
            liberar_arvore(arvore->raiz);
            printf("=============================================================================\n");
            printf("\n Pressione ENTER para voltar ao menu principal. ");
            getchar();
            getchar();
            clearScreen();
        } else if (index == 0){
            break;
        } else {
            clearScreen();
            printf("\n ERRO: Opção inválida. \n \n");
            sleep(1);
            clearScreen();
        }

    } while (index != 0);
}