//
// Created by tim on 02.01.17.
//

#include "../include/Parser.h"
#include <iostream>
#include <stdlib.h>
#include<stdarg.h>


#define DEBUG(x, y) do { std::cerr << __FILE__ << ":" << __LINE__ << ": " << x << " " << y << std::endl; } while (0)

Parser::Parser(Scanner* scanner) :
scanner(scanner),
token(nullptr)
{
}



ParseTree Parser::parse() {

    nextToken();
    auto root = this->parseProg();
    return ParseTree(root);
}

Node *Parser::parseProg() {
    auto decls = parseDecls();
    auto stmts = parseStatements();

    accept(Token::TokenType::EOF_TOKEN);

    return new Node(NodeType::Prog, decls, stmts);
}

Node *Parser::parseDecls() {
    if (token->getType() != Token::TokenType::KW_INT) {
        return new Node(NodeType::Nil);
    }

    auto decl = parseDecl();
    accept(Token::TokenType::SEMICOLON);
    return new Node(NodeType::Decls, decl, parseDecls());
}

Node *Parser::parseDecl() {
    accept(Token::TokenType::KW_INT);

    switch (token->getType()) {
        case Token::TokenType::SQUARE_BRACKET_OPEN: {
            auto arr = parseArray();
            auto ident = parseIdent();
            return new Node(NodeType ::DeclArray, arr, ident);
        }

        default: {
            auto ident = parseIdent();
            return new Node(NodeType::DeclIdent, ident);
        }
    }
}

Node *Parser::parseArray() {
    accept(Token::TokenType ::SQUARE_BRACKET_OPEN);
    auto size = parseInt();
    accept(Token::TokenType ::SQUARE_BRACKET_CLOSE);

    return new Node(NodeType::Array, size);
}

unsigned int Parser::parseInt() {
    if (token->getType() != Token::TokenType::INTEGER) {
        logError(1, Token::TokenType::INTEGER);
    }

    auto i = token->getValue();
    accept(Token::TokenType::INTEGER);
    return i;
}

Information *Parser::parseIdent() {
    if (token->getType() != Token::TokenType::IDENTIFIER) {
        logError(1, Token::TokenType::IDENTIFIER);
    }

    auto information = token->getInformation();
    accept(Token::TokenType::IDENTIFIER);
    return information;
}



Node *Parser::parseStatements() {
    switch (token->getType()) {
        case Token::TokenType::IDENTIFIER:
        case Token::TokenType::KW_WRITE:
        case Token::TokenType::KW_READ:
        case Token::TokenType::BRACKET_OPEN:
        case Token::TokenType::KW_IF:
        case Token::TokenType::KW_WHILE:
            break;
        default:
            return new Node(NodeType::Nil);
    }

    auto stmt = parseStatement();
    accept(Token::TokenType::SEMICOLON);
    return new Node(NodeType::Statements, stmt, parseStatements());
}

Node *Parser::parseStatement() {
    switch (token->getType()) {
        case Token::TokenType::IDENTIFIER: {
            auto ident = parseIdent();
            auto idx = parseIndex();
            accept(Token::TokenType::ASSIGN);
            auto exp = parseExp();
            return new Node(NodeType::StatementIdent, ident, idx, exp);
        }
        case Token::TokenType::KW_WRITE: {
            accept(Token::TokenType::KW_WRITE);
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);
            return new Node(NodeType::StatementWrite, exp);
        }
        case Token::TokenType::KW_READ: {
            accept(Token::TokenType::KW_READ);
            accept(Token::TokenType::BRACKET_OPEN);
            auto ident = parseIdent();
            auto idx = parseIndex();
            accept(Token::TokenType::BRACKET_CLOSE);
            return new Node(NodeType::StatementRead, idx, ident);
        }
        case Token::TokenType::CURLY_BRACKET_OPEN: {
            accept(Token::TokenType::CURLY_BRACKET_OPEN);
            auto stmts = parseStatements();
            accept(Token::TokenType::CURLY_BRACKET_CLOSE);
            return new Node(NodeType::StatementBlock, stmts);
        }
        case Token::TokenType::KW_IF: {
            accept(Token::TokenType::KW_IF);
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);
            auto ifStmt = parseStatement();

            if (token->getType() == Token::TokenType::KW_ELSE) {
                accept(Token::TokenType::KW_ELSE);
                auto elseStmt = parseStatement();
                return new Node(NodeType::StatementIf, exp, ifStmt, elseStmt);
            }
            return new Node(NodeType::StatementIf, exp, ifStmt,
                                   new Node(NodeType::Nil));
        }
        case Token::TokenType::KW_WHILE: {
            accept(Token::TokenType::KW_WHILE);
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);
            auto stmt = parseStatement();
            return new Node(NodeType::StatementWhile, exp, stmt);
        }
        default:
            logError(6, Token::TokenType::IDENTIFIER, Token::TokenType::KW_WRITE, Token::TokenType::KW_READ,
                     Token::TokenType::BRACKET_OPEN, Token::TokenType::KW_IF, Token::TokenType::KW_WHILE);
            // can't be reached
            return nullptr;
    }
}

Node *Parser::parseIndex() {
    if (token->getType() != Token::TokenType ::SQUARE_BRACKET_OPEN) {
        return new Node(NodeType::Nil);
    }

    accept(Token::TokenType ::SQUARE_BRACKET_OPEN);
    auto exp = parseExp();
    accept(Token::TokenType ::SQUARE_BRACKET_CLOSE);

    return new Node(NodeType::Index, exp);
}




/**
 * Accepts the given TokenType type or prints an error and exits
 * @param type The TokenType to accept
 */
void Parser::accept(Token::TokenType type) {
    DEBUG("Accept ",  Token::getTokenName( type ));

    if(this->token->getType() != type) {
        logError(1, type);
    }

    delete token; //Not needed anymore
    nextToken(); //Get next token
}

/**
 *
 */
void Parser::nextToken() {
    token = scanner->nextToken();
}

void Parser::logError(unsigned count, ...)
{
    fprintf(stderr, "unexpected token '%d' of type %s at line '%d', column '%d'",
            token->getValue(), token->getTypeStr(), token->getLine(), token->getColumn());

    va_list argptr;
    va_start(argptr, count);
    if (count > 0) {
        auto t = (Token::TokenType) va_arg(argptr, int);
        fprintf(stderr, ". Expected: '%s'", Token::valueOf(t));
    }
    for (unsigned i = 1; i < count; ++i) {
        auto t = (Token::TokenType) va_arg(argptr, int);
        fprintf(stderr, " or '%s'", Token::valueOf(t));
    }
    va_end(argptr);

    fprintf(stderr, ".\n");
    exit(1);
}

Node *Parser::parseExp() {
    auto exp2 = parseExp2();
    auto op = parseOpExp();
    return new Node(NodeType::Exp, exp2, op);
}
Node *Parser::parseExp2()
{
    switch (token->getType()) {
        case Token::TokenType::BRACKET_OPEN: {
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);
            return new Node(NodeType::Exp2, exp);
        }
        case Token::TokenType::IDENTIFIER: {
            auto ident = parseIdent();
            auto idx = parseIndex();
            return new Node(NodeType::Exp2Ident, idx, ident);
        }
        case Token::TokenType::INTEGER: {
            auto i = parseInt();
            return new Node(NodeType::Exp2Int, i);
        }
        case Token::TokenType::MINUS: {
            accept(Token::TokenType::MINUS);
            auto exp2 = parseExp2();
            return new Node(NodeType::Exp2Minus, exp2);
        }
        case Token::TokenType::NOT: {
            accept(Token::TokenType::NOT);
            auto exp2 = parseExp2();
            return new Node(NodeType::Exp2Neg, exp2);
        }
        default:
            logError(5, Token::TokenType::BRACKET_OPEN, Token::TokenType::IDENTIFIER, Token::TokenType::INTEGER,
                     Token::TokenType::MINUS, Token::TokenType::NOT);
            // can't be reached
            return nullptr;
    }
}

Node *Parser::parseOpExp()
{
    switch (token->getType()) {
        case Token::TokenType::PLUS:
        case Token::TokenType::MINUS:
        case Token::TokenType::STAR:
        case Token::TokenType::COLON:
        case Token::TokenType::LESS:
        case Token::TokenType::GREATER:
        case Token::TokenType::EQUAL:
        case Token::TokenType::EXPRESSION_EQUAL:
        case Token::TokenType::AND:
            break;

        default:
            return new Node(NodeType::Nil);
    }

    auto op = parseOp();
    auto exp = parseExp();
    return new Node(NodeType::OpExp, op, exp);
}

Node *Parser::parseOp()
{
    switch (token->getType()) {
        case Token::TokenType::PLUS:
        case Token::TokenType::MINUS:
        case Token::TokenType::STAR:
        case Token::TokenType::COLON:
        case Token::TokenType::LESS:
        case Token::TokenType::GREATER:
        case Token::TokenType::EQUAL:
        case Token::TokenType::EXPRESSION_EQUAL:
        case Token::TokenType::AND: {
            auto n = new Node(NodeType::Op, token);
            nextToken();
            return n;
        }
        default:
            return new Node(NodeType::Nil);
    }
}







