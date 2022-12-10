/*
    E' P T' M num n
    消除左递归后的文法(@表示空串):
    E -> TP
    P -> +TP | -TP | @
    T -> FM
    M -> *FM | /FM | @
    F -> (E) | n

    FIRST(E) = {"(", "n"}    FOLLOW(E) = {")", "$"}
    FIRST(P) = {"+", "-", "@" }    FOLLOW(P) = {")", "$"}
    FIRST(T) = {"(", "n"}    FOLLOW(T) = {"+", "-", "$"}
    FIRST(M) = {"*", "/", "@"}    FOLLOW(M) = {"+", "-", ")", "$"}
    FIRST(F) = {"(", "n"}    FOLLOW(F) = {"*", "/", "$"}
    
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supple.h"

void prepare(nonterminal **nonal) {
    *nonal = (nonterminal *)malloc(sizeof(nonterminal) * 5);
    
    (*nonal) -> cur = 'E';
    (*nonal) -> fol = (generator *)malloc(sizeof(generator));
    (*nonal) -> fol -> formual = "TP";
    (*nonal) -> fol -> next = NULL;
    
    (*nonal + 1) -> cur = 'P';
    (*nonal + 1) -> fol = (generator *)malloc(sizeof(generator));
    (*nonal + 1) -> fol -> formual = "+TP";
    (*nonal + 1) -> fol -> next = (generator *)malloc(sizeof(generator));
    (*nonal + 1) -> fol -> next -> formual = "-TP";
    (*nonal + 1) -> fol -> next -> next = (generator *)malloc(sizeof(generator));
    (*nonal + 1) -> fol -> next -> next -> formual = "@";
    (*nonal + 1) -> fol -> next -> next -> next = NULL;

    (*nonal + 2) -> cur = 'T';
    (*nonal + 2) -> fol = (generator *)malloc(sizeof(generator));
    (*nonal + 2) -> fol -> formual = "FM";
    (*nonal + 2) -> fol -> next = NULL;

    (*nonal + 3) -> cur = 'M';
    (*nonal + 3) -> fol = (generator *)malloc(sizeof(generator));
    (*nonal + 3) -> fol -> formual = "*FM";
    (*nonal + 3) -> fol -> next = (generator *)malloc(sizeof(generator));
    (*nonal + 3) -> fol -> next -> formual = "/FM";
    (*nonal + 3) -> fol -> next -> next = (generator *)malloc(sizeof(generator));
    (*nonal + 3) -> fol -> next -> next -> formual = "@";
    (*nonal + 3) -> fol -> next -> next -> next = NULL;

    (*nonal + 4) -> cur = 'F';
    (*nonal + 4) -> fol = (generator *)malloc(sizeof(generator));
    (*nonal + 4) -> fol -> formual = "(E)";
    (*nonal + 4) -> fol -> next = (generator *)malloc(sizeof(generator));
    (*nonal + 4) -> fol -> next -> formual = "n";
    (*nonal + 4) -> fol -> next -> next = NULL;

}

bool is_generator(char c) {
    
    if (c == 'E' || c == 'P' || c == 'T' || c == 'M' || c == 'F' || c == '@')
        return false;
    return true;

}

char *FIRST(char c) {
    if (c == 'E') {
        return "(n";
    } else if (c == 'P') {
        return "+-@";
    } else if (c == 'T') {
        return "(n";
    } else if (c == 'M') {
        return "*/@";
    } else {
        return "(n";
    }
}

char *FOLLOW(char c) {
    if (c == 'E') {
        return ")$";
    } else if (c == 'P') {
        return ")$";
    } else if (c == 'T') {
        return "+-$";
    } else if (c == 'M') {
        return "+-)$";
    } else {
        return "*/$";
    }
}