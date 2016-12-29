/**
 * @file     Token.cpp
 * @author   Bob
 * @date     29/12/2016
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
    _value(0),
    _errorToken(nullptr)
{
}


Token::Token(TokenType type, const int& line, const int& column, const unsigned int& value) :
    _type(type),
    _line(line),
    _column(column),
    _value(value),
    _errorToken(nullptr)
{
}


Token::Token(TokenType type, const int& line, const int& column, Information* information) :
    _type(type),
    _line(line),
    _column(column),
    _information(information),
    _value(0),
    _errorToken(nullptr)
{
}


Token::Token(TokenType type, const int& line, const int& column, const char* errorToken) :
    _type(type),
    _line(line),
    _column(column),
    _value(0),
    _errorToken(errorToken)
{
}


const char* Token::getLexem() const
{
    if (this->_information == nullptr)
        return "No Infromation";

    return this->_information->getName();
}


const char* Token::getErrorToken() const
{
    if (this->_errorToken == nullptr)
        return "No Error Token";

    return this->_errorToken;
}


Token::~Token()
{
    // Delete error token
    if (this->_errorToken != nullptr)
        delete[] this->_errorToken;
}
