//
// Created by tim on 04.11.15.
//

#ifndef HSKA_COMPILER_INFORMATION_H
#define HSKA_COMPILER_INFORMATION_H

#include "../../scanner/include/Token.h"

class Information {
private:
    Token::TokenType type;
    char* lexem;

public:
    Information(Token::TokenType type, char const * lexem);

    bool compareLex(char const* lexem);
    char const * getName();

    Token::TokenType getType();
};


#endif //HSKA_COMPILER_INFORMATION_H
