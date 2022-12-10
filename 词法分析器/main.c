#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "init.h"
#include "tool.h"
#include "lexemer.h"

void result_display(Symbol *symbols) {

    for (int i = 0; i < symbol_count; i++) {
        printf("[Line] : %d\n", symbols[i].line);
        printf("[Type] : %s\n", symbols[i].type);
        printf("[Value] : %s\n\n", symbols[i].value);  
    }

    printf("The number of rows in this source file : %d\n", line);
    printf("The number of characters in this source file : %d\n", characters);

    for (int i = 0; i < 6; ++i) {
        printf("[%s] : %d\n", words[i].type, words[i].num);
    }

    return;
}

int main(int argc, char **argv) {

    Symbol *symbols = (Symbol *)malloc(sizeof(Symbol));
    scanning(argv[1], &symbols);
    result_display(symbols);
    
    return 0;
}
