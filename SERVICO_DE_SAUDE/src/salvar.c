#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/cadastro.h"
#include "../include/clearscreen.h"
#include "../include/limpabuffer.h"

int salvar_lista(Lista *lista) {
    FILE *file = fopen("lista.bin", "wb");
    if (file == NULL) {
        return -1;
    }

    fwrite(&lista->qtde, sizeof(int), 1, file);

    ELista *atual = lista->primeiro;
    while (atual !=  NULL) {
        fwrite(atual->dados, sizeof(Registro), 1, file);
        fwrite(atual->dados->entrada, sizeof(Data), 1, file);
        atual = atual->proximo;
    }

    fclose(file);
    return 0;
}

int carregar_lista(Lista *lista) {
    FILE *file = fopen("lista.bin", "rb");
    if (file == NULL) {
        return -1;
    }

    fread(&lista->qtde, sizeof(int), 1, file);
    lista->primeiro = NULL;

    for (int i = 0; i < lista->qtde; i++) {
        Registro *registro = malloc(sizeof(Registro));
        Data *data = malloc(sizeof(Data));

        fread(registro, sizeof(Registro), 1, file);
        fread(data, sizeof(Data), 1, file);

        ELista *novo_elemento = criar_Elista(registro);

        novo_elemento->dados->entrada = malloc(sizeof(Data));

        novo_elemento->dados->entrada->dia = data->dia;
        novo_elemento->dados->entrada->mes = data->mes;
        novo_elemento->dados->entrada->ano = data->ano;

        if (lista->primeiro == NULL) {
            lista->primeiro = novo_elemento;
        } else {
            ELista *atual = lista->primeiro;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novo_elemento;
        }
        free(data);
    }
    fclose(file);
    return 0;
}