#ifndef CADASTRO_H
#define CADASTRO_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char nome[100];
    char rpg[20];
    int idade;
    Data *entrada;
} Registro;

typedef struct {
    struct ELista *proximo;
    Registro *dados;
} ELista;

typedef struct {
    ELista *primeiro;
    int qtde;
} Lista;

#endif
