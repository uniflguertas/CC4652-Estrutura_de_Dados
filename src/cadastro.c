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

}
