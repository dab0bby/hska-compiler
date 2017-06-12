//
// Created by tim on 02.01.17.
//

#include "../include/Node.h"
#include "../../utils/include/colormod.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

Node::Node(NodeType type, Node *n1) :
        nodeType(type),
        children {n1, nullptr, nullptr},
        information(nullptr),
        token(nullptr),
        value(0)
{

}

Node::Node(NodeType type, Node *n1, Node *n2) :
        nodeType(type),
        children {n1, n2, nullptr},
        information(nullptr),
        token(nullptr),
        value(0)
{
}

Node::Node(NodeType type, Node *n1, Node *n2, Node *n3) :
        nodeType(type),
        children {n1, n2, n3},
        information(nullptr),
        token(nullptr),
        value(0)
{
}

Node::Node(NodeType type, Information *information) :
        nodeType(type),
        children {nullptr, nullptr, nullptr},
        information(information),
        token(nullptr),
        value(0)
{

}

Node::Node(NodeType type, Node *n1, Information *information) :
        nodeType(type),
        children {n1, nullptr, nullptr},
        information(information),
        token(nullptr),
        value(0)
{

}

Node::Node(NodeType type, Information *information, Node *n1, Node *n2) :
        nodeType(type),
        children {n1, n2, nullptr},
        information(information),
        token(nullptr),
        value(0)
{

}

Node::Node(NodeType type) :
        nodeType(type),
        children {nullptr, nullptr, nullptr},
        information(nullptr),
        token(nullptr),
        value(0)
{
}

Node::Node(NodeType type, unsigned int intValue) :
        nodeType(type),
        children {nullptr, nullptr, nullptr},
        information(nullptr),
        token(nullptr),
        value(intValue)
{

}

Node::Node(NodeType type, Token *token) :
        nodeType(type),
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

    if (token != nullptr)
        delete token;
}

Node *Node::getDecl() const
{
    switch (nodeType) {
        case Decls:
            return children[0];
        default:
            error("decl");
            return nullptr;
    }
}

Node *Node::getDecls() const
{
    switch (nodeType) {
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
    switch (nodeType) {
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
    switch (nodeType) {
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
    switch (nodeType) {
        case DeclArray:
            return children[0];
        default:
            error("arr");
            return nullptr;
    }
}

Node *Node::getExp() const
{
    switch (nodeType) {
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
    switch (nodeType) {
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
    switch (nodeType) {
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
    switch (nodeType) {
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
    switch (nodeType) {
        case StatementIf:
            return children[1];
        default:
            error("ifStatement");
            return nullptr;
    }
}

Node *Node::getElseStatement() const
{
    switch (nodeType) {
        case StatementIf:
            return children[2];
        default:
            error("elseStatement");
            return nullptr;
    }
}

Information *Node::getInformation() const
{
    switch (nodeType) {
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
    switch (nodeType) {
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
    switch (nodeType) {
        case Op:
            return token;
        default:
            error("token");
            return nullptr;
    }
}


void Node::dump() {
    dump(0);
}

NodeType Node::getNodeType() const
{
    return nodeType;
}

void Node::dump(int i) {
    //Intend
    for(int j=0; j<i; j++)
        cout << "  ";

    //Print Node
    cout << "-" << typeToString(nodeType);


    if(nodeType == Op) {
        cout << " " << this->token->getTokenName(this->token->getType());
    } else if(nodeType == Exp2Int || nodeType == Array){
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
    cout << Color::Modifier(Color::FG_RED) << "Unsupported function called: " << functionName << " for NodeType: " << typeToString(this->nodeType) << Color::Modifier(Color::FG_DEFAULT) << endl;
    exit(1);
}


Node *Node::makeStatementWrite(Node *exp) {
    return new Node(StatementWrite, exp);
}

Node *Node::makeStatementBlock(Node *statements) {
    return new Node(StatementBlock, statements);
}

Node *Node::makeIndex(Node *exp) {
    return new Node(NodeType::Index, exp);
}

Node *Node::makeType(Node *exp) {
    return new Node(NodeType::Exp2, exp);
}

Node *Node::makeExp2Minus(Node *exp2) {
    return new Node(NodeType::Exp2Minus, exp2);
}

Node *Node::makeExp2Neg(Node *exp2) {
    return new Node(NodeType::Exp2Neg, exp2);
}

Node *Node::makeProg(Node *decls, Node *statements) {
    return new Node(NodeType::Prog, decls, statements);
}

Node *Node::makeDecls(Node *decl, Node *decls) {
    return new Node(NodeType::Decls, decl, decls);
}

Node *Node::makeStatements(Node *statement, Node *statements) {
    return new Node(NodeType::Statements, statement, statements);
}

Node *Node::makeStatementWhile(Node *exp, Node *statement) {
    return new Node(NodeType::StatementWhile, exp, statement);
}

Node *Node::makeExp(Node *exp2, Node *op) {
    return new Node(NodeType::Exp, exp2, op);
}

Node *Node::makeOpExp(Node *op, Node *exp) {
    return new Node(NodeType::OpExp, op, exp);
}

Node *Node::makeStatementIf(Node *exp, Node *ifStmt, Node *elseStmt) {
    return new Node(NodeType::StatementIf, exp, ifStmt, elseStmt);
}

Node *Node::makeNil() {
    return new Node(NodeType::Nil);
}

Node *Node::makeDeclIdent(Information *ident) {
    return new Node(NodeType::DeclIdent, ident);
}

Node *Node::makeDeclArray(Node *arr, Information *ident) {
    return new Node(NodeType ::DeclArray, arr, ident);
}

Node *Node::makeStatementRead(Node *idx, Information *ident) {
    return new Node(NodeType::StatementRead, idx, ident);
}

Node *Node::makeExp2Ident(Node *idx, Information *ident) {
    return new Node(NodeType::Exp2Ident, idx, ident);
}

Node *Node::makeStatementIdent(Information *ident, Node *idx, Node *exp) {
    return new Node(NodeType::StatementIdent, ident, idx, exp);
}

Node *Node::makeArray(unsigned int size) {
    return new Node(NodeType::Array, size);
}

Node *Node::makeExp2Int(unsigned int i) {
    return new Node(NodeType::Exp2Int, i);
}

Node *Node::makeOp(Token *token) {
    return new Node(NodeType::Op, token);
}


