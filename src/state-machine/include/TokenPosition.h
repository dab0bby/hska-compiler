#pragma once

#include "../../scanner/include/Token.h"

class TokenPosition
{
public:
    TokenPosition() { }
    TokenPosition(Token::TokenType token, int begin, int size, int offset = 0) : token(token), begin(begin), size(size), offset(offset)  { }
    
    Token::TokenType token = Token::DETECTING;
    int begin = 0;
    int size = 0;
    int offset = 0;

    TokenPosition* getNext() const;
    void setNext(TokenPosition* next);

    TokenPosition* getPrevious() const;
    void setPrevious(TokenPosition* previous);

    static void deleteAllPrevious(TokenPosition* token);
    static void deleteAllNext(TokenPosition* token);
    static void offsetAll(TokenPosition* token, int offset);
    static void jumpToFirst(TokenPosition*& token);
    static void jumpToLast(TokenPosition*& token);

private:
    TokenPosition* _previous = nullptr;
    TokenPosition* _next = nullptr;
};
