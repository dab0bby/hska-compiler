//
// Created by Bob on 13.12.2016.
//


#include "../include/Token.h"


Token::Token(TokenType type, const int &line, const int &column) :
    _type(type),
    _line(line),
    _column(column)
{
}


Token::~Token()
{

}
