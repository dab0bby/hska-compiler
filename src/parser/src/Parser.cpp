//
// Created by tim on 02.01.17.
//

#include "../../utils/include/colormod.h"
#include "../include/Parser.h"

#include <iostream>
#include <stdlib.h>
#include <stdarg.h>


#define DEBUG(x, y) do { std::cerr << __FILE__ << ":" << __LINE__ << ": " << x << " " << y << std::endl; } while (0)

using namespace std;

Parser::Parser(Scanner* scanner) :
scanner(scanner),
token(nullptr),
prevToken(nullptr)
{
}



ParseTree* Parser::parse() {

    nextToken();
    auto root = this->parseProg();
    return new ParseTree(root);
}

Node *Parser::parseProg() {
    auto decls = parseDecls();
    auto statements = parseStatements();

    accept(Token::TokenType::EOF_TOKEN);

    return Node::makeProg(decls, statements, token);
}

Node *Parser::parseDecls() {
    if (token->getType() != Token::TokenType::KW_INT) {
        return Node::makeNil();
    }

    auto decl = parseDecl();
    accept(Token::TokenType::SEMICOLON);
    return Node::makeDecls(decl, parseDecls(), token);
}

Node *Parser::parseDecl() {
    accept(Token::TokenType::KW_INT);

    auto startToken = token;

    switch (token->getType()) {
        case Token::TokenType::SQUARE_BRACKET_OPEN: {
            auto arr = parseArray();
            auto ident = parseIdent();
            return Node::makeDeclArray(arr, ident, startToken);
        }

        default: {

            auto ident = parseIdent();
            return Node::makeDeclIdent(ident, startToken);
        }
    }
}

Node *Parser::parseArray() {
    accept(Token::TokenType ::SQUARE_BRACKET_OPEN);
    auto startToken = token;
    auto size = parseInt();
    accept(Token::TokenType ::SQUARE_BRACKET_CLOSE);

    return Node::makeArray(size, startToken);
}

unsigned int Parser::parseInt() {
    if (token->getType() != Token::TokenType::INTEGER) {
        error(1, Token::TokenType::INTEGER);
    }

    auto i = token->getValue();
    accept(Token::TokenType::INTEGER);
    return i;
}

Information *Parser::parseIdent() {
    if (token->getType() != Token::TokenType::IDENTIFIER) {
        error(1, Token::TokenType::IDENTIFIER);
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
        case Token::TokenType::CURLY_BRACKET_OPEN:
        case Token::TokenType::KW_IF:
        case Token::TokenType::KW_WHILE:
            break;
        default:
            return Node::makeNil();
    }

    auto startToken = token;
    auto statement = parseStatement();
    accept(Token::TokenType::SEMICOLON);
    return Node::makeStatements(statement, parseStatements(), startToken);
}

Node *Parser::parseStatement() {
    auto startToken = token;
    switch (token->getType()) {
        case Token::TokenType::IDENTIFIER: {
            auto ident = parseIdent();
            auto idx = parseIndex();
            accept(Token::TokenType::ASSIGN);
            auto exp = parseExp();
            return Node::makeStatementIdent(ident, idx, exp, startToken);
        }
        case Token::TokenType::KW_WRITE: {
            accept(Token::TokenType::KW_WRITE);
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);

            return Node::makeStatementWrite(exp, startToken);
        }
        case Token::TokenType::KW_READ: {
            accept(Token::TokenType::KW_READ);
            accept(Token::TokenType::BRACKET_OPEN);
            auto ident = parseIdent();
            auto idx = parseIndex();
            accept(Token::TokenType::BRACKET_CLOSE);
            return Node::makeStatementRead(idx, ident, startToken);
        }
        case Token::TokenType::CURLY_BRACKET_OPEN: {
            accept(Token::TokenType::CURLY_BRACKET_OPEN);
            auto statements = parseStatements();
            accept(Token::TokenType::CURLY_BRACKET_CLOSE);

            return Node::makeStatementBlock(statements, startToken);
        }
        case Token::TokenType::KW_IF: {
            accept(Token::TokenType::KW_IF);
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);
            auto ifStmt = parseStatement();

            if (token->getType() == Token::TokenType::KW_ELSE) {
                auto elseToken = token;
                accept(Token::TokenType::KW_ELSE);
                auto elseStmt = parseStatement();
                return Node::makeStatementIf(exp, ifStmt, elseStmt, elseToken);
            }
            return Node::makeStatementIf(exp, ifStmt, Node::makeNil(), startToken);
        }
        case Token::TokenType::KW_WHILE: {
            accept(Token::TokenType::KW_WHILE);
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);
            auto statement = parseStatement();
            return Node::makeStatementWhile(exp, statement, startToken);
        }
        default:
            error(6, Token::TokenType::IDENTIFIER, Token::TokenType::KW_WRITE, Token::TokenType::KW_READ,
                  Token::TokenType::BRACKET_OPEN, Token::TokenType::KW_IF, Token::TokenType::KW_WHILE);
            // can't be reached
            return nullptr;
    }
}

Node *Parser::parseIndex() {
    if (token->getType() != Token::TokenType ::SQUARE_BRACKET_OPEN) {
        return Node::makeNil();
    }

    auto openToken = token;
    accept(Token::TokenType ::SQUARE_BRACKET_OPEN);
    auto exp = parseExp();
    accept(Token::TokenType ::SQUARE_BRACKET_CLOSE);

    return Node::makeIndex(exp, openToken);
}




/**
 * Accepts the given TokenType type or prints an error and exits
 * @param type The TokenType to accept
 */
void Parser::accept(Token::TokenType type) {
    //DEBUG("Accept ",  Token::getTokenName( type ));

    if(this->token->getType() != type) {
        error(1, type);
    }

    nextToken(); //Get next token
}

/**
 *
 */
void Parser::nextToken() {
    prevToken = token;
    token = scanner->nextToken();
}


Node *Parser::parseExp() {
    auto startToken = token;
    auto exp2 = parseExp2();
    auto op = parseOpExp();
    return Node::makeExp(exp2, op, startToken);
}
Node *Parser::parseExp2()
{
    auto startToken = token;
    switch (token->getType()) {
        case Token::TokenType::BRACKET_OPEN: {
            accept(Token::TokenType::BRACKET_OPEN);
            auto exp = parseExp();
            accept(Token::TokenType::BRACKET_CLOSE);
            return Node::makeType(exp, startToken);
        }
        case Token::TokenType::IDENTIFIER: {
            auto ident = parseIdent();
            auto idx = parseIndex();
            return Node::makeExp2Ident(idx, ident, startToken);
        }
        case Token::TokenType::INTEGER: {
            auto i = parseInt();

            return Node::makeExp2Int(i, startToken);
        }
        case Token::TokenType::MINUS: {
            accept(Token::TokenType::MINUS);
            auto exp2 = parseExp2();
            return Node::makeExp2Minus(exp2, startToken);
        }
        case Token::TokenType::NOT: {
            accept(Token::TokenType::NOT);
            auto exp2 = parseExp2();
            return Node::makeExp2Neg(exp2, startToken);
        }
        default:
            error(5, Token::TokenType::BRACKET_OPEN, Token::TokenType::IDENTIFIER, Token::TokenType::INTEGER,
                  Token::TokenType::MINUS, Token::TokenType::NOT);
            // can't be reached
            return nullptr;
    }
}

Node *Parser::parseOpExp()
{
    auto startToken = token;
    switch (token->getType()) {
        case Token::TokenType::PLUS:
        case Token::TokenType::MINUS:
        case Token::TokenType::STAR:
        case Token::TokenType::COLON:
        case Token::TokenType::LESS:
        case Token::TokenType::GREATER:
        case Token::TokenType::EQUAL:
        case Token::TokenType::UNEQUAL:
        case Token::TokenType::AND:
            break;

        default:
            return Node::makeNil();
    }

    auto op = parseOp();
    auto exp = parseExp();
    return Node::makeOpExp(op, exp, startToken);
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
        case Token::TokenType::UNEQUAL:
        case Token::TokenType::AND: {
            auto n = Node::makeOp(token);
            nextToken();
            return n;
        }
        default:
            return Node::makeNil();
    }
}

/**
 * Prints an error message on the console and quits the program
 * @param count The number of expected TokenTypes
 */
void Parser::error(unsigned count, ...) {

    cerr << Color::Modifier(Color::FG_RED) << "unexpected token ";
    if (token->getType() == Exp2Int || token->getType() == Array) {
        cerr << "'" << token->getValue() << "' ";
    } else if(token->getType() == StatementIdent) {
        cerr << "'" << token->getInformation()->getName() << "' ";
    }
    cerr << "of type '" << token->getTypeStr() << "' at line: " << token->getLine() << " column: " << token->getColumn();

    va_list argptr;
    va_start(argptr, count);
    if (count > 0) {
        auto t = (Token::TokenType) va_arg(argptr, int);
        cerr << " Expected: '" << Token::valueOf(t) << "'";
    }
    for (unsigned i = 1; i < count; ++i) {
        auto t = (Token::TokenType) va_arg(argptr, int);
        cerr << " or '" << Token::valueOf(t) << "'";
    }
    va_end(argptr);
    cerr << Color::Modifier(Color::FG_DEFAULT) << endl;

    exit(1);
}





