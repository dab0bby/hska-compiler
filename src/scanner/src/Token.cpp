/**
 * @file     Token.cpp
 * @author   Bob
 * @date     20/12/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include "../include/Token.h"
#include "../../symbol-table/include/Information.h"


Token::Token(TokenType type, const int &line, const int &column) :
    _type(type),
    _line(line),
    _column(column),
    _value(0)
{
}


Token::Token(TokenType type, const int& line, const int& column, const unsigned int& value) :
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
    _information(information),
    _value(0)
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
