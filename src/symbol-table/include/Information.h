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
    Information(Token::TokenType type, const char * lexem);

    bool compareLex(const char* lexem) const;
    const char* getName() const;

    Token::TokenType getType();
};


#endif //HSKA_COMPILER_INFORMATION_H
