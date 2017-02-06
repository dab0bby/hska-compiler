//
// Created by tim on 02.01.17.
//

#ifndef HSKA_COMPILER_PARSER_H
#define HSKA_COMPILER_PARSER_H


#include "../../scanner/include/Token.h"
#include "../../scanner/include/Scanner.h"
#include "ParseTree.h"
#include "Node.h"

class Parser {

public:
    Parser(Scanner *scanner);

    ParseTree parse();
private:
    Scanner *scanner;
    Token *token;

    Node *parseProg();
    Node *parseDecls();
    Node *parseStatements();
    Node *parseDecl();
    Node *parseArray();
    Node *parseStatement();
    Node *parseIndex();
    Node *parseExp();
    Node *parseExp2();
    Node *parseOpExp();
    Node *parseOp();
    Information *parseIdent();
    unsigned int parseInt();

    void accept(Token::TokenType token);
    void nextToken();

    void logError(unsigned count, ...);

};


#endif //HSKA_COMPILER_PARSER_H
