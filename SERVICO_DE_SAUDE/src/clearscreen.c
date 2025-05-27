#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/clearscreen.h"

void clearScreen() {
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
  }
  