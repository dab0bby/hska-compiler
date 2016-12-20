//
// Created by tim on 04.11.15.
//

#include "../include/Information.h"

#include <cstring>


Information::Information(Token::TokenType type, const char* lexem) : type(type)
{
    auto size = strlen(lexem);
    this->lexem = new char[size];
    strncpy((char*)this->lexem, lexem, size);
}


bool Information::compareLex(char const * lexem) {
    return strcmp(this->lexem, lexem) == 0;
}

const char * Information::getName() {
    return (char const*)this->lexem;
}


Token::TokenType Information::getType() {
    return this->type;
}

