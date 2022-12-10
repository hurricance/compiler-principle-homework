#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supple.h"

int main(void) {
    nonterminal *nonal;
    prepare(&nonal);
    form *analysis_table;

    get_analysis_table(&analysis_table, nonal);
    puts("The forecast analysis table is as follows:");
    for (int i = 0; i < 5; ++i) {
        char c = (analysis_table + i)-> begin;
        printf("%c:\n", c);
        table *show = (analysis_table + i) -> next;
        while (show != NULL) {
            printf("%c %c -> %s\n", show -> cur, c, show -> process);
            show = show -> next;
        }
        putchar('\n');
    }
    analysis_program(analysis_table);
    return 0;
}