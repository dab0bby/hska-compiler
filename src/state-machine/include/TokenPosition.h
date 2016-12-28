#pragma once

#include "../../scanner/include/Token.h"

class TokenPosition
{
public:
    TokenPosition() { }
    TokenPosition(Token::TokenType token, int position, int size) : token(token), position(position), size(size)  { }
    
    Token::TokenType token = Token::DETECTING;
    int position = 0;
    int size = 0;

    TokenPosition* getNext() const;
    void setNext(TokenPosition* next);

    TokenPosition* getPrevious() const;
    void setPrevious(TokenPosition* previous);
    static void deleteAllPrevious(TokenPosition* token);
    static void deleteAllNext(TokenPosition* token);

private:
    TokenPosition* _previous = nullptr;
    TokenPosition* _next = nullptr;
};
