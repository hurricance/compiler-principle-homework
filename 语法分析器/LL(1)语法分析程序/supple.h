#include <stdbool.h>
#define BUFFER_SIZE 100

typedef struct generator {
    char *formual;
    struct generator *next;
}generator;

typedef struct {
    char cur;
    generator *fol;
}nonterminal;

typedef struct table {
    char cur;
    char *process;
    struct table *next;
}table;

typedef struct {
    char begin;
    table *next;
}form;

typedef struct Stack{
    char item[BUFFER_SIZE];
    int len;
} Stack;


void prepare(nonterminal **nonal);
bool is_generator(char c);
char *FIRST(char c);
char *FOLLOW(char c);
void get_analysis_table(form **analysis_table, nonterminal *nonal);
void analysis_program(form *analysis_table);