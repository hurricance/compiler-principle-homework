#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "supple.h"

void get_analysis_table(form **analysis_table, nonterminal *nonal) {
    
    *analysis_table = (form *)malloc(sizeof(form) * 5);

    for (int i = 0; i < 5; ++i) {
        
        (*analysis_table + i) -> begin = (nonal + i) -> cur;
        generator *temp = (nonal + i) -> fol;
        (*analysis_table + i) -> next = (table *)malloc(sizeof(table));
        table *p = (*analysis_table + i)-> next;
        table *fe = NULL;

        while (temp != NULL) {
            
            char c = (temp -> formual)[0];

            if (is_generator(c)) {

                p -> cur = c;
                p -> process = temp -> formual;
                p -> next = (table *)malloc(sizeof(table));
                fe = p;
                p = p -> next;

            } else if (c == '@') {

                char *s = FOLLOW((nonal + i) -> cur);

                for (int i = 0; i < strlen(s); ++i) {
                    
                    p -> cur = s[i];
                    p -> process = temp -> formual;
                    p -> next = (table *)malloc(sizeof(table));
                    fe = p;
                    p = p -> next;
                    
                }
                
            } else {
                char *s = FIRST(c);

                for (int i = 0; i < strlen(s); ++i) {
                    
                    p -> cur = s[i];
                    p -> process = temp -> formual;
                    p -> next = (table *)malloc(sizeof(table));
                    fe = p;
                    p = p -> next;

                }

            }

            temp = temp -> next;
        
        }

        free(p);
        fe -> next = NULL;
    
    }

}

void analysis_program(form *analysis_table) {

    char input[BUFFER_SIZE], output[BUFFER_SIZE] = "@";
    puts("Please enter the string you want to analyze:");
    scanf("%s", input);
    printf("\n%s", "Stack   input   output\n");
    strcat(input, "$");
    Stack stack;
    stack.len = 1;
    stack.item[0] = '$';
    stack.item[1] = 'E';
    int i = 0;
    int p = stack.len;

    while (p != -1) {
        
        for (int j = 0; j <= p; ++j) {
            putchar(stack.item[j]);
        }
        printf("    ");
        for (int j = i; j < strlen(input); ++j) {
            putchar(input[j]);
        }
        printf("    ");
        printf("%s\n", output);
        memset(output, 0, sizeof(output));
        output[0] = '@';
        
        if (is_generator(stack.item[p])) {

            if (input[i] != stack.item[p]) {
                
                puts("failed to match");
                return;

            } else {
                --p;
                ++i;
            }

        } else {

            int base = 0;
            switch (stack.item[p]) {
                case 'E':
                    base = 0;
                    break;
                case 'P':
                    base = 1;
                    break;

                case 'T':
                    base = 2;
                    break;
                
                case 'M':
                    base = 3;
                    break;
                
                case 'F':
                    base = 4;
                    break;
            }

            table *temp = (analysis_table + base) -> next;

            while (temp != NULL) {

                if (temp -> cur == input[i]) {

                    output[0] = (analysis_table + base) -> begin;
                    strcat(output, " -> ");
                    strcat(output, temp -> process);
                    for (int k = (strlen(temp -> process) - 1); k >= 0; --k) {
                        if ((temp -> process)[k] == '@') {
                            break;
                        }
                        stack.item[p++] = (temp -> process)[k];
                    }
                    --p;
                    break;
                }

                temp = temp -> next;
            }

            if (temp == NULL) {
                puts("fail to match");
                return;
            }
        }
    }
    puts("success to match");
    return;
}