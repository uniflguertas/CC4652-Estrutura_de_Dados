#ifndef PESQUISA_H
#define PESQUISA_H
#include "../include/cadastro.h"

typedef struct Vertice {
    Registro *registro;
    struct Vertice* esquerdo;
    struct Vertice* direito;
    struct Vertice* pai;
} Vertice;

typedef struct Arvore {
    Vertice* raiz;
    int qtde;
} Arvore;

void menuitem_pesquisa();
void liberar_arvore(Vertice* vertice);
void inserir(Arvore* arvore,int modo);
Arvore *cria_arvore();
Vertice *cria_vertice(Registro *registro);


#endif