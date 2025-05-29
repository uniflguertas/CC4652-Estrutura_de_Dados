#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/salvar.h"
#include "../include/cadastro.h"
#include "../include/atendimento.h"
#include "../include/limpabuffer.h"

// Cria um novo elemento da fila (EFila) que armazena um registro de paciente
EFila *criar_Efila(Registro *registro) {
    EFila *efila = malloc(sizeof(EFila));  // aloca memória para o elemento
    efila->proximo = NULL;                  // inicializa ponteiro próximo como NULL
    efila->dados = registro;                // associa o registro ao elemento

    return efila;
}

// Cria a estrutura da fila, inicializando ponteiros e quantidade zerados
Fila *criar_fila() {
    Fila *fila = malloc(sizeof(Fila));  // aloca memória para a fila
    fila->head = NULL;                   // início da fila vazio
    fila->tail = NULL;                   // fim da fila vazio
    fila->qtde = 0;                     // quantidade de elementos zero

    return fila;
}

// Cria uma célula para a pilha (Stack), copiando os dados do registro
Celula *criar_celula (Registro *registro, int m) {
    Celula *celula = malloc(sizeof(Celula));   // aloca memória para a célula
    celula->anterior = NULL;                    // inicializa ponteiros nulos
    celula->proximo = NULL;

    // Copia dados do registro para a célula (cópia profunda)
    celula->registro = malloc(sizeof(Registro));
    strcpy(celula->registro->nome, registro->nome);
    strcpy(celula->registro->rg, registro->rg);
    celula->registro->idade = registro->idade;

    // Copia dados da data de entrada
    celula->registro->entrada = malloc(sizeof(Data));
    celula->registro->entrada->dia = registro->entrada->dia;
    celula->registro->entrada->mes = registro->entrada->mes;
    celula->registro->entrada->ano = registro->entrada->ano;

    celula->modo = m;  // armazena o modo da operação (1=enfileirar, 2=desenfileirar)
    return celula;
}

// Cria a estrutura da pilha (Stack), inicializando topo e quantidade
Stack *criar_stack(){
    Stack *stack = malloc(sizeof(Stack));  // aloca memória para a pilha
    stack->topo = NULL;                    // topo inicialmente nulo
    stack->qtde = 0;                      // sem elementos
    return stack;
}

// Insere um novo registro na pilha (push)
void push(Stack *stack, Registro *registro, int m){
    Celula *novo = criar_celula(registro, m);  // cria nova célula
    if(stack->qtde > 0){                        // se já houver elementos na pilha
        novo->anterior = stack->topo;           // novo aponta para o topo atual
        stack->topo->proximo = novo;            // topo atual aponta para novo
    }
    stack->topo = novo;                         // novo elemento vira topo
    stack->qtde++;                              // incrementa quantidade
}

// Remove o elemento do topo da pilha (pop) e desfaz a operação correspondente na fila
void pop(Stack *stack, Fila *fila) {
    if (stack->qtde >= 1) {
        Celula *atual = stack->topo;           // pega o topo da pilha
        if (atual->modo == 1) {                 // se operação foi enfileirar
            desfazer_enfileirar(fila);          // desfaz enfileiramento na fila
        } else {                               // se operação foi desenfileirar
            desfazer_desenfileirar(fila, atual->registro); // desfaz desenfileiramento
        }
        stack->topo = stack->topo->anterior;   // topo passa para o elemento anterior
        // libera memória da célula removida
        free(atual->registro->entrada);
        free(atual->registro);           
        free(atual);
        stack->qtde--;                          // decrementa quantidade da pilha
    }
    return;
}

// Desfaz a operação de enfileiramento: remove o último paciente da fila
void desfazer_enfileirar(Fila *fila){
    if (fila->qtde > 0) {
        EFila *atual = fila->head;
        EFila *temp = NULL;
        if (fila->qtde == 1) {      // se só tiver um paciente na fila
            fila->head = NULL;       // fila fica vazia
            fila->tail = NULL;
        } else {
            // percorre até o penúltimo elemento
            while (atual->proximo != NULL) {
                temp = atual;
                atual = atual->proximo;
            }
            fila->tail = temp;        // penúltimo vira o último
            fila->tail->proximo = NULL; // remove o último da fila
        }
        printf("RG do desenfileirado: %s \n", atual->dados->nome);
        // libera memória do registro removido
        free(atual->dados->entrada);
        free(atual->dados);
        free(atual);
        fila->qtde--;                 // decrementa quantidade da fila
    } else {
        printf("Fila vazia!");
    }
}

// Desfaz a operação de desenfileiramento: insere o registro no início da fila
void desfazer_desenfileirar(Fila *fila, Registro *registro) {
    if (registro != NULL) {
        EFila *novo = criar_Efila(registro);  // cria novo elemento com registro
        novo->proximo = fila->head;            // novo aponta para o início atual
        fila->head = novo;                     // novo vira início da fila
        if (fila->tail == NULL) {              // se fila estava vazia
            fila->tail = novo;                 // novo também é o fim
        }
        fila->qtde++;                         // incrementa quantidade
    } 
}

// Mostra a operação que será desfeita no topo da pilha, retornando uma mensagem
char* mostrar_pop(Stack *stack) {
    if (stack->qtde == 0) {
        system("clear");
        printf("\n Não há ações para desfazer. \n \n");
        sleep(1);
        system("clear");
        return NULL;
    }
    Celula *topo = stack->topo;
    char *mensagem = malloc(300 * sizeof(char)); 
    if (topo->modo == 1) {
        snprintf(mensagem, 300, "ENFILEIRAMENTO DO PACIENTE %s (RG: %s)", 
                 topo->registro->nome, topo->registro->rg);
    } else if (topo->modo == 2) {
        snprintf(mensagem, 300, "DESENFILEIRAMENTO DO PACIENTE %s (RG: %s)", 
                 topo->registro->nome, topo->registro->rg);
    } 
    return mensagem; 
}

// Verifica se o RG existe na lista geral de pacientes e retorna o registro
Registro* verifica_rg(char rg[20]) {
    Lista *lista = malloc(sizeof(Lista));
    carregar_lista(lista);  // carrega a lista de registros cadastrados

    ELista *atual = lista->primeiro;
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;   // procura o RG na lista
    }

    if (atual == NULL) {        // RG não encontrado
        system("clear");
        printf("\n ERRO: RG inválido.\n \n");
        sleep(2);
        system("clear");
        return NULL;
    } else {
        return atual->dados;     // retorna o registro encontrado
    }
    liberar_lista(lista);        // libera a lista (embora aqui nunca chegue)
}

// Verifica se o paciente com o RG já está na fila (retorna 0 se já estiver)
int verificar_enfileiramento(Fila *fila, char rg[20]) {
    EFila *atual = fila->head;

    while(atual != NULL) {
        if(strcmp(atual->dados->rg, rg) == 0) {
            return 0;  // paciente já está enfileirado
        }
        atual = atual->proximo;
    }
    return 1;  // paciente não está na fila
}

// Enfileira paciente na fila caso RG seja válido e paciente não esteja enfileirado
void enfileirar(Fila *fila, char rg[20], Stack *stack) {
    Registro *registro = verifica_rg(rg);  // verifica existência do paciente

    if(registro != NULL && verificar_enfileiramento(fila, rg) == 1) {
        EFila *novo = criar_Efila(registro);  // cria novo elemento da fila
        if (fila->qtde == 0) {
            fila->head = novo;  // fila vazia, novo elemento vira início
        } else {
            fila->tail->proximo = novo;  // adiciona no final da fila
        }
        fila->tail = novo;  // novo elemento é o novo final da fila
        fila->qtde++;      // incrementa quantidade
        push(stack, registro, 1);  // registra ação na pilha para desfazer depois

        system("clear");
        printf("==================================================\n");
        printf("ENFILEIRAR PACIENTE\n");
        printf("==================================================\n");
        printf("\n %s enfileirado com sucesso! \n \n", novo->dados->nome);
        sleep(2);
        system("clear");
    } else {
        system("clear");
        printf("\n ERRO: RG inválido ou já enfileirado.");
        sleep(2);
        system("clear");
    }
}

// Remove paciente do início da fila e registra ação na pilha para possível desfazer
void desenfileirar(Fila *fila, Stack *stack) {
    if (fila->qtde > 0) {
        EFila *efila = fila->head;      // guarda o primeiro elemento da fila
        fila->head = fila->head->proximo;  // avança o início da fila

        if(fila->qtde == 1) {           // se só tinha um paciente
            fila->tail = NULL;           // fila fica vazia
        }
        fila->qtde--;                   // decrementa quantidade
        push(stack,  efila->dados, 2);  // registra ação de desenfileirar na pilha

        system("clear");
        printf("==================================================\n");
        printf("DESENFILEIRAR PACIENTE\n");
        printf("==================================================\n");
        printf("\n %s desenfileirado com sucesso! \n \n", efila->dados->nome);
        sleep(2);
        system("clear");

        // libera memória do registro removido
        free(efila->dados->entrada);
        free(efila->dados);
        free(efila);
    } else {
        system("clear");
        printf("\n ERRO: Não há pacientes para desenfileirar.");
        sleep(2);
        system("clear");
    }
}

// Mostra a fila de pacientes com seus dados na tela
void mostrar_fila(Fila *fila) {
    EFila *atual = fila->head;
    int contador = 0;
    printf("==================================================\n");
    printf("FILA DE PACIENTES\n");
    printf("==================================================\n");
    
    if(atual == NULL && contador == 0) {
        printf("\n Nenhum paciente encontrado.\n \n");
    } else {
        while(atual != NULL) {
            printf(" NOME: %s\n", atual->dados->nome);
            printf(" RG: %s\n", atual->dados->rg);
            printf(" DATA DE ENTRADA: %d/%d/%d\n \n",
                atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
            atual = atual->proximo;
        }
    }
    printf("==================================================\n");
    printf("\n Pressione ENTER para voltar ao menu principal. ");
    getchar();
    getchar();
}

// Libera toda a memória alocada pela fila, removendo todos os pacientes
void liberar_fila(Fila *fila) {
    while (fila->qtde > 0) {  
        EFila *temp = fila->head;
        fila->head = fila->head->proximo;
        if (fila->qtde == 1) {
            fila->tail = NULL;
        }
        fila->qtde--;
        free(temp->dados->entrada);
        free(temp->dados);
        free(temp);
    }
}

// Menu principal para atendimento com opções para enfileirar, desenfileirar e mostrar fila
int menuitem_atendimento(Fila *fila, Stack *stack) {
    int index;
    char rg[20];

    do {
        printf("================================================== \n");
        printf("2. ATENDIMENTO\n");
        printf("================================================== \n");
        printf(" Digite o número da opção desejada abaixo: \n");
        printf(" 1. Enfileirar paciente\n");
        printf(" 2. Desenfileirar paciente\n");
        printf(" 3. Mostrar fila\n");
        printf("\n Insira 0 para voltar ao menu principal.\n");
        printf("================================================== \n");
        printf("Digite aqui: ");
        scanf("%d", &index);

        switch(index) {
            case 1: {
                system("clear");
                printf("\n Insira o RG do paciente que deseja enfileirar: ");
                scanf("%s", rg);
                enfileirar(fila, rg, stack);  // chama função para enfileirar
                system("clear");
                break;
            }
            case 2: {
                system("clear");
                desenfileirar(fila, stack);   // chama função para desenfileirar
                break;
            }
            case 3: {
                system("clear");
                mostrar_fila(fila);           // exibe a fila atual
                system("clear");
                break;
            }
            case 0: {
                system("clear");
                break;                       // sai do menu
            }
            default: {
                system("clear");
                printf("\n404 - Not Found\n \n");
                sleep(1);
                system("clear");
                break;
            }            
        }

    } while(index != 0);
    return 0;
}
