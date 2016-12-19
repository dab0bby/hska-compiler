//
// Created by Bob on 13.12.2016.
//


#include "../include/Token.h"
#include "../../symbol-table/include/Information.h"


Token::Token(TokenType type, const int &line, const int &column) :
    _type(type),
    _line(line),
    _column(column)
{
}


Token::Token(TokenType type, const int& line, const int& column, const int& value) :
    _type(type),
    _line(line),
    _column(column),
    _value(value)
{
}


Token::Token(TokenType type, const int& line, const int& column, Information* information) :
    _type(type),
    _line(line),
    _column(column),
    _information(information)
{
}


const char* Token::getLexem() const
{
    if (this->_information == nullptr)
        return "No Infromation";

    return this->_information->getName();
}


Token::~Token()
{
}
