void skip_blank(char *buffer, char *c, int *end) {
    
    if (*c != ' ') {
        return;
    }

    while (buffer[*end] == ' ') {
        (*end)++;
    }
    *c = buffer[*end];
    (*end)++;

}

void get_next(char *buffer, char *c, int *end) {
    
    *c = buffer[*end];
    (*end)++;
    return;

}

void token_connect(char *token, char c) {
    
    char temp[2] = {c};
    strcat(token, temp);
    return;

}

int is_keyword(char *str) {
    
    for (int i = 0; i < 32; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;

}

void table_insert(int kind, char *token, Symbol **symbols) {

    symbol_count++;
    *symbols = (Symbol *)realloc(*symbols, sizeof(Symbol) * (symbol_count));
    strcpy((*symbols)[symbol_count - 1].value, token);
    (*symbols)[symbol_count - 1].line = line;
    
    switch (kind) {
        case 0:
            (*symbols)[symbol_count - 1].type = "Keyword";
            break;
        case 1:
            (*symbols)[symbol_count - 1].type = "Identifier";
            break;
        case 2:
            (*symbols)[symbol_count - 1].type = "Integer";
            break;
        case 3:
            (*symbols)[symbol_count - 1].type = "Float";
            break;
        case 4:
            (*symbols)[symbol_count - 1].type = "Punctuation";
            break;
        case 5:
            (*symbols)[symbol_count - 1].type = "Unknown";
            break;
    }
    return;
}

void error(char *token, Symbol **symbols) {

    words[5].num += 1;
    table_insert(5, token, symbols);
    printf("there is an error in the row %d\n", line);
    return;

}