#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/limpabuffer.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}