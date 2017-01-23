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


const char *Token::valueOf(Token::TokenType type) {
    switch (type) {
        case DETECTING:
            return "<detecting>";
        case IGNORE:
            return "<ignore>";
        case ERROR:
            return "<error>";
        case EOF_TOKEN:
            return "<eof>";
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case COLON:
            return ":";
        case NOT:
            return "!";
        case STAR:
            return "*";
        case LESS:
            return "<";
        case GREATER:
            return ">";
        case EQUAL:
            return "=";
        case ASSIGN:
            return ":=";
        case EXPRESSION_EQUAL:
            return "=:=";
        case AND:
            return "&";
        case SEMICOLON:
            return ";";
        case BRACKET_OPEN:
            return "(";
        case BRACKET_CLOSE:
            return ")";
        case CURLY_BRACKET_OPEN:
            return "{";
        case CURLY_BRACKET_CLOSE:
            return "}";
        case SQUARE_BRACKET_OPEN:
            return "[";
        case SQUARE_BRACKET_CLOSE:
            return "]";
        case KW_IF:
            return "if";
        case KW_ELSE:
            return "else";
        case KW_WHILE:
            return "while";
        case KW_WRITE:
            return "write";
        case KW_READ:
            return "read";
        case KW_INT:
            return "int";
        case IDENTIFIER:
            return "<identifier>";
        case INTEGER:
            return "<number>";
    default:
            return "Unknown";
    }
}
