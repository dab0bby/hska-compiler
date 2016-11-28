//
// Created by tim on 04.11.15.
//

#include "../include/Information.h"

#include <cstring>


Information::Information(Token::TokenType type, char const* lexem) : type(type) {
    this->lexem = new char[sizeof (lexem)];
    strncpy(this->lexem, lexem, sizeof(this->lexem));

}


bool Information::compareLex(char const * lexem) {
    return strcmp(this->lexem, lexem) == 0;
}

char const *Information::getName() {
    return (char const*)this->lexem;
}


Token::TokenType Information::getType() {
    return this->type;
}

