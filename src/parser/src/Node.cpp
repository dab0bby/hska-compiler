//
// Created by tim on 02.01.17.
//

#include "../include/Node.h"
#include "../../utils/include/colormod.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

Node::Node(NodeType type, Node *n1, Token* token) :
        type(type),
        children {n1, nullptr, nullptr},
        information(nullptr),
        token(token),
        value(0)
{

}

Node::Node(NodeType type, Node *n1, Node *n2, Token* token) :
        type(type),
        children {n1, n2, nullptr},
        information(nullptr),
        token(token),
        value(0)
{
}

Node::Node(NodeType type, Node *n1, Node *n2, Node *n3, Token* token) :
        type(type),
        children {n1, n2, n3},
        information(nullptr),
        token(token),
        value(0)
{
}

Node::Node(NodeType type, Information *information, Token* token) :
        type(type),
        children {nullptr, nullptr, nullptr},
        information(information),
        token(token),
        value(0)
{

}

Node::Node(NodeType type, Node *n1, Information *information, Token* token) :
        type(type),
        children {n1, nullptr, nullptr},
        information(information),
        token(token),
        value(0)
{

}

Node::Node(NodeType type, Information *information, Node *n1, Node *n2, Token* token) :
        type(type),
        children {n1, n2, nullptr},
        information(information),
        token(token),
        value(0)
{

}

Node::Node(NodeType type) :
        type(type),
        children {nullptr, nullptr, nullptr},
        information(nullptr),
        token(nullptr),
        value(0)
{
}

Node::Node(NodeType type, unsigned int intValue, Token* token) :
        type(type),
        children {nullptr, nullptr, nullptr},
        information(nullptr),
        token(token),
        value(intValue)
{

}

Node::Node(NodeType type, Token* token) :
        type(type),
        children {nullptr, nullptr, nullptr},
        information(nullptr),
        token(token),
        value(0)
{
}

Node::~Node() {
    for (int i = 0; i < 3; i++)
        if (children[i] != nullptr)
            delete children[i];


        //TODO Who is deleting tokens?
    //if (token != nullptr)
       // delete token;
}

Node *Node::getDecl() const
{
    switch (type) {
        case Decls:
            return children[0];
        default:
            error("decl");
            return nullptr;
    }
}

Node *Node::getDecls() const
{
    switch (type) {
        case Prog:
            return children[0];
        case Decls:
            return children[1];
        default:
            error("decls");
            return nullptr;
    }
}

Node *Node::getStatement() const
{
    switch (type) {
        case Statements:
            return children[0];
        case StatementWhile:
            return children[1];
        default:
            return nullptr;
    }
}

Node *Node::getStatements() const
{
    switch (type) {
        case Prog:
            return children[1];
        case StatementBlock:
            return children[0];
        case Statements:
            return children[1];
        default:
            error("stmts");
            return nullptr;
    }
}


Node *Node::getArray() const
{
    switch (type) {
        case DeclArray:
            return children[0];
        default:
            error("arr");
            return nullptr;
    }
}

Node *Node::getExp() const
{
    switch (type) {
        case StatementIdent:
            return children[1];
        case StatementWrite:
            return children[0];
        case StatementIf:
            return children[0];
        case StatementWhile:
            return children[0];
        case Exp2:
            return children[0];
        case Index:
            return children[0];
        case OpExp:
            return children[1];
        default:
            error("exp");
            return nullptr;
    }
}

Node *Node::getExp2() const
{
    switch (type) {
        case Exp:
            return children[0];
        case Exp2Minus:
            return children[0];
        case Exp2Neg:
            return children[0];
        default:
            error("exp2");
            return nullptr;
    }
}

Node *Node::getOp() const
{
    switch (type) {
        case Exp:
            return children[1];
        case OpExp:
            return children[0];
        default:
            error("op");
            return nullptr;
    }
}

Node *Node::getIndex() const
{
    switch (type) {
        case StatementIdent:
            return children[0];
        case StatementRead:
            return children[0];
        case Exp2Ident:
            return children[0];
        default:
            error("index");
            return nullptr;
    }
}

Node *Node::getIfStatement() const
{
    switch (type) {
        case StatementIf:
            return children[1];
        default:
            error("ifStatement");
            return nullptr;
    }
}

Node *Node::getElseStatement() const
{
    switch (type) {
        case StatementIf:
            return children[2];
        default:
            error("elseStatement");
            return nullptr;
    }
}

Information *Node::getInformation() const
{
    switch (type) {
        case DeclArray:
        case DeclIdent:
        case StatementIdent:
        case StatementRead:
        case Exp2Ident:
            return information;
        default:
            error("information");
            return nullptr;
    }
}

unsigned int Node::getIntValue() const
{
    switch (type) {
        case Array:
        case Exp2Int:
            return value;
        default:
            error("intValue");
            return 0;
    }
}

Token* Node::getToken() const
{
    switch (type) {
        case Nil:
            error("token""");
            return nullptr;
        default:
            return token;
    }
}


void Node::dump() {
    dump(0);
}

void Node::dump(int i) {
    //Intend
    for(int j=0; j<i; j++)
        cout << "  ";

    //Print Node
    cout << "-" << typeToString(type);


    if(type == Op) {
        cout << " " << this->token->getTokenName(this->token->getType());
    } else if(type == Exp2Int || type == Array){
        cout << " Value:" << this->value;
    }

    if(information != nullptr)
        cout << " Lexem: " << information->getName();
    cout << endl;

    //Print children
    for (int x = 0; x < 3; x++)
        if (children[x] != nullptr)
            children[x]->dump(i + 1);
}

const char *Node::typeToString(NodeType type) {
    switch(type) {
        case Prog:
            return "Prog";
        case Decls:
            return "Decls";
        case DeclArray:
            return "DeclArray";
        case DeclIdent:
            return "DeclIdent";
        case Array:
            return "Array";
        case    Statements:
            return "Statements";
        case    StatementIdent:
            return "StatementIdent";
        case    StatementWrite:
            return "StatementWrite";
        case    StatementRead:
            return "StatementRead";
        case    StatementIf:
            return "StatementIf";
        case    StatementWhile:
            return "StatementWhile";
        case    StatementBlock:
            return "StatementBlock";
        case    Exp:
            return "Exp";
        case    Exp2:
            return "Exp2";
        case    Exp2Ident:
            return "Exp2Ident";
        case    Exp2Int:
            return "Exp2Int";
        case    Exp2Minus:
            return "Exp2Minus";
        case    Exp2Neg:
            return "Exp2Neg";
        case    Index:
            return "Index";
        case    OpExp:
            return "OpExp";
        case    Op:
            return "Op";
        case    Nil:
            return "Nil";
        default:
            return "Unknown";
    }
}

void Node::error(const char *functionName) const {
    cout << Color::Modifier(Color::FG_RED) << "Unsupported function called: " << functionName << " for NodeType: " << typeToString(this->type) << Color::Modifier(Color::FG_DEFAULT) << endl;
    exit(1);
}


Node *Node::makeStatementWrite(Node *exp, Token* token) {
    return new Node(StatementWrite, exp, token);
}

Node *Node::makeStatementBlock(Node *statements, Token* token) {
    return new Node(StatementBlock, statements, token);
}

Node *Node::makeIndex(Node *exp, Token* token) {
    return new Node(NodeType::Index, exp, token);
}

Node *Node::makeType(Node *exp, Token* token) {
    return new Node(NodeType::Exp2, exp, token);
}

Node *Node::makeExp2Minus(Node *exp2, Token* token) {
    return new Node(NodeType::Exp2Minus, exp2, token);
}

Node *Node::makeExp2Neg(Node *exp2, Token* token) {
    return new Node(NodeType::Exp2Neg, exp2, token);
}

Node *Node::makeProg(Node *decls, Node *statements, Token* token) {
    return new Node(NodeType::Prog, decls, statements, token);
}

Node *Node::makeDecls(Node *decl, Node *decls, Token* token) {
    return new Node(NodeType::Decls, decl, decls, token);
}

Node *Node::makeStatements(Node *statement, Node *statements, Token* token) {
    return new Node(NodeType::Statements, statement, statements, token);
}

Node *Node::makeStatementWhile(Node *exp, Node *statement, Token* token) {
    return new Node(NodeType::StatementWhile, exp, statement, token);
}

Node *Node::makeExp(Node *exp2, Node *op, Token* token) {
    return new Node(NodeType::Exp, exp2, op, token);
}

Node *Node::makeOpExp(Node *op, Node *exp, Token* token) {
    return new Node(NodeType::OpExp, op, exp, token);
}

Node *Node::makeStatementIf(Node *exp, Node *ifStmt, Node *elseStmt, Token* token) {
    return new Node(NodeType::StatementIf, exp, ifStmt, elseStmt, token);
}

Node *Node::makeNil() {
    return new Node(NodeType::Nil);
}

Node *Node::makeDeclIdent(Information *ident, Token* token) {
    return new Node(NodeType::DeclIdent, ident, token);
}

Node *Node::makeDeclArray(Node *arr, Information *ident, Token* token) {
    return new Node(NodeType ::DeclArray, arr, ident, token);
}

Node *Node::makeStatementRead(Node *idx, Information *ident, Token* token) {
    return new Node(NodeType::StatementRead, idx, ident, token);
}

Node *Node::makeExp2Ident(Node *idx, Information *ident, Token* token) {
    return new Node(NodeType::Exp2Ident, idx, ident, token);
}

Node *Node::makeStatementIdent(Information *ident, Node *idx, Node *exp, Token* token) {
    return new Node(NodeType::StatementIdent, ident, idx, exp, token);
}

Node *Node::makeArray(unsigned int size, Token* token) {
    return new Node(NodeType::Array, size, token);
}

Node *Node::makeExp2Int(unsigned int i, Token* token) {
    return new Node(NodeType::Exp2Int, i, token);
}

Node *Node::makeOp(Token *token) {
    return new Node(NodeType::Op, token);
}


