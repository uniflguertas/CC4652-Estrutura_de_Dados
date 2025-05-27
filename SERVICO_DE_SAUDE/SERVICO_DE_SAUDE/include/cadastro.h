#ifndef CADASTRO_H
#define CADASTRO_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char nome[100];
    char rg[20];
    int idade;
    Data *entrada;
} Registro;

typedef struct ELista{
    Registro *dados;
    struct ELista *proximo;
} ELista;

typedef struct {
    ELista *primeiro;
    int qtde;
} Lista;

int menuitem_cadastro(void);

#endif