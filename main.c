#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}

int main(void) {

    int index;

    do {
        clearScreen();
        printf("Seja bem-vindo ao Serviço de Atendimento de Saúde. \n");
        printf("O que gostaria de fazer hoje? \n");    
        printf("================================================== \n");
        printf("Digite o número da opção desejada abaixo: \n");
        printf("\n");
        printf("1. Cadastrar\n");
        printf("2. Atendimento\n");
        printf("3. Atendimento Prioritário\n");
        printf("4. Pesquisa\n");
        printf("5. Desfazer\n");
        printf("6. Carregar/Salvar\n");
        printf("7. Sobre\n");
        printf("8. Sair\n");
        printf("==================================================");

        printf("\nDigite aqui: ");
        scanf("%d", &index);
    }
    while (index != 8);

    clearScreen();
    printf("\n Encerrando... \n \n");
    sleep(1);
    clearScreen();
    
    return 0;
}
