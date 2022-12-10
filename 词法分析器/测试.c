/*
    This is the file for testing
*/

void scanning(char *path, Symbol **symbols) {
    @
    float a = 0.E;
    float c = 0.1E@;
    float c = 0.1E+A;

    int state = 0;
    int end;
    char c;

    label:
    while (fgets(buffer, fp) != NULL) {

        characters += strlen(buffer);
        ++line;
        end = 0;
        char token[35];

        for (; end < strlen(buffer);) {

            switch (state) {

                case 0:

                    memset(token, '\0', sizeof(token));
                    getnext(buffer, &c, &end);
                    skipblank(buffer, &c, &end);

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
                        || c == '{' || c == '}') {
                        words[4].num += 1;
                        char temp[2] = {c};
                        tableinsert(4, temp, symbols);
                    } else {
                        state = 13;
                    }
                    
                    break;

                case 1:

                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);

                    if (isdigit(c) || isalpha(c)) {
                        state = 1;
                    } else {
                        
                        --end;
                        state = 0;
                        
                        if (iskeyword(token)) {
                            words[0].num += 1;
                            tableinsert(0, token, symbols);
                        } else {
                            words[1].num += 1;
                            tableinsert(1, token, symbols);
                        }
                    
                    }
                    
                    break;
                
                case 2:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    
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
                        tableinsert(2, token, symbols);
                    }
                    
                    break;

                case 3:

                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    
                    if (isdigit(c)) {
                        state = 4;
                    } else {
                        error();
                        state = 0;
                    }
                    
                    break;

                case 4:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    
                    if (c >= '0' && c <= '9') {
                        state = 4;
                    } else if (c == 'E') {
                        state = 5;
                    } else {
                        --end;
                        state = 0;
                        words[3].num += 1;
                        tableinsert(3, token, symbols);
                    }
                    
                    break;
                
                case 5:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    
                    if (c >= '0' && c <= '9') {
                        state = 7;
                    } else if (c == '-' || c == '+') {
                        state = 6;
                    } else {
                        error();
                        state = 0;
                    }
                    
                    break;

                case 6:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    
                    if (isdigit(c)) {
                        state = 7;
                    } else {
                        error();
                        state = 0;
                    }
                    
                    break;

                case 7:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    
                    if (isdigit(c)) {
                        state = 7;
                    } else {
                        --end;
                        state = 0;
                        words[3].num += 1;
                        tableinsert(3, token, symbols);
                    }
                    
                    break;
                
                case 8:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    words[3].num += 1;

                    if (c == '=' || c == '<') {
                        tokenconnect(token, c);
                        state = 0;
                        tableinsert(4, token, symbols);
                    } else {
                        --end;
                        state = 0;
                        tableinsert(4, token, symbols);
                    }
                    
                    break;

                case 9:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    words[3].num += 1;

                    if (c == '=' || c == '>') {
                        tokenconnect(token, c);
                        state = 0;
                        tableinsert(4, token, symbols);
                    } else {
                        --end;
                        state = 0;
                        tableinsert(4, token, symbols);
                    }
                    
                    break;

                case 10:
                    
                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    words[4].num += 1;

                    if (c == '=') {
                        tokenconnect(token, c);
                        state = 0;
                        tableinsert(4, token, symbols);
                    } else {
                        --end;
                        state = 0;
                        tableinsert(4, token, symbols);
                    }
                    
                    break;
                
                case 11:

                    tokenconnect(token, c);
                    getnext(buffer, &c, &end);
                    if (c == '*') {
                        state = 12;
                    } else {
                        end--;
                        state = 0;
                        words[3].num += 1;
                        tableinsert(4, token, symbols);
                    }
                    
                    break;
                
                case 12:

                    getnext(buffer, &c, &end);
                    while (c != '*') {
                        getnext(buffer, &c, &end);
                        if (c == '\n');
                        goto label;
                    }
                    getnext(buffer, &c, &end);
                    if (c == '/') {
                        state = 0;
                    } else {
                        state = 12;
                    }
                    
                    break;

                case 13:
                    
                    error();
                    state = 0;
                    break;
            
            }
        }
    }
}