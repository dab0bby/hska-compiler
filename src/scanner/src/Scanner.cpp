/**
 * @file     Scanner.cpp
 * @author   Bob
 * @date     30/12/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include <cstdlib>
#include <errno.h>
#include <iostream>
#include <cstring>

#include "../include/Scanner.h"


Scanner::Scanner(Buffer* buffer, SymbolTable* symbolTable, TokenScanner* tokenScanner) :
    _buffer(buffer),
    _symbolTable(symbolTable),
    _tokenScanner(tokenScanner)
{
}


Token* Scanner::nextToken()
{
    Token* token = nullptr;
    TokenPosition* tokens = nullptr;
    char c = 0;

    // Check for pending Tokens
    if (this->_pendingTokens != nullptr)
        tokens = this->_pendingTokens;
    else
        c = this->_buffer->nextChar();

    while (tokens == nullptr)
    {
        if (this->_tokenScanner->consume(c))
        {
            // Get tokens
            tokens = this->_tokenScanner->getPendingTokens();

            if (tokens != nullptr)
            {
                if (tokens->token != Token::TokenType::NEW_LINE)
                    break;
                else // NEW_LINE tokens are ignored
                    tokens = nullptr;
            }
        }

        // No tokens found yet. Read next char
        c = this->_buffer->nextChar();
    }

    switch (tokens->token)
    {
        case Token::TokenType::IDENTIFIER:
            token = this->_createIdentifier(tokens->size, tokens->offset);
            break;
        case Token::TokenType::INTEGER:
            token = this->_createInteger(tokens->size, tokens->offset);
            break;
        case Token::TokenType::ERROR:
            token = this->_createError(tokens->size, tokens->offset);
            break;
        default:
            token = new Token(tokens->token, this->_buffer->getLineNum(), this->_getTokenBegin(tokens->size, tokens->offset));
            break;
    }

    // Check for further tokens
    this->_checkForPendingToken(tokens);

    // Cleanup
    delete tokens;

    return token;
}


/**
 * Creates an identifier Token
 * @return
 */
Token* Scanner::_createIdentifier(const int& size, const int& offset) const
{
    // Get string and insert into symbolTable
    auto str = this->_buffer->subStr(size, offset);
    auto information = this->_symbolTable->insert(str, Token::TokenType::IDENTIFIER);
    delete[] str;

    const int begin = this->_getTokenBegin(size, offset);

    if(information->compareLex("while")) {
        return new Token(Token::TokenType::KW_WHILE, this->_buffer->getLineNum(), begin, information);
    } else if(information->compareLex("int")) {
        return new Token(Token::TokenType::KW_INT, this->_buffer->getLineNum(), begin, information);
    } else {
        return new Token(Token::TokenType::IDENTIFIER, this->_buffer->getLineNum(), begin, information);
    }
}


/**
 * Creates an integer Token
 * @return
 */
Token* Scanner::_createInteger(const int& size, const int& offset) const
{
    // Get string and try to cast to integer
    auto str = this->_buffer->subStr(size, offset);

    const int begin = this->_getTokenBegin(size, offset);

    errno = 0;
    auto value = strtol(str, NULL, 10);

    // Check for errors
    if (errno == ERANGE)
    {
        // Print error
        std::cerr << "Number out of range: " << str << std::endl;

        errno = 0;
        delete[] str; // Delete string
        return new Token(Token::TokenType::ERROR, this->_buffer->getLineNum(), begin);
    }

    delete[] str;
    return new Token(Token::TokenType::INTEGER, this->_buffer->getLineNum(), begin, value);
}


/**
 * Creates a new Error token
 */
Token* Scanner::_createError(const int& size, const int& offset) const
{
    // Get string
    auto str = this->_buffer->subStr(size, offset);
    const int begin = this->_getTokenBegin(size, offset);

    // Don't delete strbecause Token is the new owner
    return new Token(Token::TokenType::ERROR, this->_buffer->getLineNum(), begin, str);
}


/**
 * Return the beginning position of current token
 * @return
 */
int Scanner::_getTokenBegin(const int& size, const int& offset) const
{
    return this->_buffer->getColumnNum() - size - offset;
}


/**
 * Checks if there is a next Token available.
 * If so it is added to the pendingTokens list
 */
void Scanner::_checkForPendingToken(TokenPosition* tokens)
{
    auto next = tokens->getNext();
    if (next == nullptr)
    {
        this->_pendingTokens = nullptr;
        return;
    }

    // Ignore the NEW_LINE token
    if (next->token == Token::TokenType::NEW_LINE)
    {
        this->_checkForPendingToken(next);
        delete next; // delete it because its never used/ignored
    }
    else
        this->_pendingTokens = next;
}


Scanner::~Scanner()
{
    // Clear pending tokens
    if (this->_pendingTokens != nullptr)
    {
        TokenPosition::deleteAllPrevious(this->_pendingTokens);
        TokenPosition::deleteAllNext(this->_pendingTokens);
        delete this->_pendingTokens;
    }
}
