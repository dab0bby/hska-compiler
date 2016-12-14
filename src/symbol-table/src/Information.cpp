//
// Created by tim on 04.11.15.
//

#include "../include/Information.h"

#include <cstring>


Information::Information(Token::TokenType type, char const* lexem) : type(type) {
    auto size = sizeof(lexem);
    this->lexem = new char[sizeof(size)];
    strncpy(this->lexem, lexem, sizeof(size));
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

