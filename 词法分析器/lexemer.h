void scanning(char *path, Symbol **symbols) {

    FILE *fp = fopen(path, "r");
    
    if (fp == NULL) {
        printf("Couldn't open file %s\n", path);
        return;
    }


    char buffer[BUFFER_SIZE];
    int state = 0;
    int end;
    char c;

    label:
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {

        characters += strlen(buffer);
        ++line;
        end = 0;
        char token[35];

        for (; end < strlen(buffer);) {

            switch (state) {

                case 0:

                    memset(token, '\0', sizeof(token));
                    get_next(buffer, &c, &end);
                    skip_blank(buffer, &c, &end);

                    if (c == '\n') {
                        goto label;
                    }
                    
                    if (isalpha(c)) {
                        state = 1;
                    } else if (isdigit(c)) {
                        state = 2;
                    } else if (c == '<') {
                        state = 8;
                    } else if (c == '>') {
                        state = 9;
                    } else if (c == '=') {
                        state = 10;
                    } else if (c == '/') {
                        state = 11;
                    } else if (c == ':' || c == '+' || c == '-' || c == '*' 
                        || c == '(' || c == ')' || c == ';' || c == '\\'
                        || c == '{' || c == '}' || c == '\'' || c == '&'
                        || c == ',' || c == '[' || c == ']' || c == '.' 
                        || c == '!' || c == '|') {
                        words[4].num += 1;
                        char temp[2] = {c};
                        table_insert(4, temp, symbols);
                    } else {
                        state = 13;
                    }
                    
                    break;

                case 1:

                    token_connect(token, c);
                    get_next(buffer, &c, &end);

                    if (isdigit(c) || isalpha(c)) {
                        state = 1;
                    } else {
                        
                        --end;
                        state = 0;
                        
                        if (is_keyword(token)) {
                            words[0].num += 1;
                            table_insert(0, token, symbols);
                        } else {
                            words[1].num += 1;
                            table_insert(1, token, symbols);
                        }
                    
                    }
                    
                    break;
                
                case 2:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    
                    if (c >= '0' && c <= '9') {
                        state = 2;
                    } else if (c == '.') {
                        state = 3;
                    } else if (c == 'E') {
                        state = 5;
                    } else {
                        --end;
                        state = 0;
                        words[2].num += 1;
                        table_insert(2, token, symbols);
                    }
                    
                    break;

                case 3:

                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    
                    if (isdigit(c)) {
                        state = 4;
                    } else {
                        error(token, symbols);
                        state = 0;
                    }
                    
                    break;

                case 4:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    
                    if (c >= '0' && c <= '9') {
                        state = 4;
                    } else if (c == 'E') {
                        state = 5;
                    } else {
                        --end;
                        state = 0;
                        words[3].num += 1;
                        table_insert(3, token, symbols);
                    }
                    
                    break;
                
                case 5:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    
                    if (c >= '0' && c <= '9') {
                        state = 7;
                    } else if (c == '-' || c == '+') {
                        state = 6;
                    } else {
                        error(token, symbols);
                        state = 0;
                    }
                    
                    break;

                case 6:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    
                    if (isdigit(c)) {
                        state = 7;
                    } else {
                        error(token, symbols);
                        state = 0;
                    }
                    
                    break;

                case 7:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    
                    if (isdigit(c)) {
                        state = 7;
                    } else {
                        --end;
                        state = 0;
                        words[3].num += 1;
                        table_insert(3, token, symbols);
                    }
                    
                    break;
                
                case 8:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    words[4].num += 1;

                    if (c == '=' || c == '<') {
                        token_connect(token, c);
                        state = 0;
                        table_insert(4, token, symbols);
                    } else {
                        --end;
                        state = 0;
                        table_insert(4, token, symbols);
                    }
                    
                    break;

                case 9:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    words[4].num += 1;

                    if (c == '=' || c == '>') {
                        token_connect(token, c);
                        state = 0;
                        table_insert(4, token, symbols);
                    } else {
                        --end;
                        state = 0;
                        table_insert(4, token, symbols);
                    }
                    
                    break;

                case 10:
                    
                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    words[4].num += 1;

                    if (c == '=') {
                        token_connect(token, c);
                        state = 0;
                        table_insert(4, token, symbols);
                    } else {
                        --end;
                        state = 0;
                        table_insert(4, token, symbols);
                    }
                    
                    break;
                
                case 11:

                    token_connect(token, c);
                    get_next(buffer, &c, &end);
                    if (c == '*') {
                        state = 12;
                    } else {
                        end--;
                        state = 0;
                        words[4].num += 1;
                        table_insert(4, token, symbols);
                    }
                    
                    break;
                
                case 12:

                    get_next(buffer, &c, &end);
                    while (c != '*') {
                        get_next(buffer, &c, &end);
                        if (c == '\n');
                        goto label;
                    }
                    get_next(buffer, &c, &end);
                    if (c == '/') {
                        state = 0;
                    } else {
                        state = 12;
                    }
                    
                    break;

                case 13:
                    char temp[2] = {c};
                    strcat(token, temp);
                    error(token, symbols);
                    state = 0;
                    break;
            
            }
        }
    }
}