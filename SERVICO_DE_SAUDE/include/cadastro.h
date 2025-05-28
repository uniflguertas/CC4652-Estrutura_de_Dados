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

int menuitem_cadastro(Lista *lista);
Lista *criar_lista();
ELista *criar_Elista(Registro *registro);
void cadastrar(Lista *lista);
void consultar_paciente(Lista *lista, char rg[20]);
void mostrar_lista(Lista *lista);
void atualizar_paciente(Lista *lista, char rg[20]);
void remover_paciente(Lista *lista, char rg[20]);
void liberar_lista(Lista *lista);
#endif