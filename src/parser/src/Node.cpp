//
// Created by tim on 02.01.17.
//

#include "../include/Node.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

Node::Node(NodeType type, Node *n1) :
        type(type),
        children {n1, nullptr, nullptr},
        information(nullptr),
        token(nullptr),
        value(0)
{

}

Node::Node(NodeType type, Node *n1, Node *n2) :
        type(type),
        children {n1, n2, nullptr},
        information(nullptr),
        token(nullptr),
        value(0)
{
}

Node::Node(NodeType type, Node *n1, Node *n2, Node *n3) :
        type(type),
        children {n1, n2, n3},
        information(nullptr),
        token(nullptr),
        value(0)
{
}

Node::Node(NodeType type, Information *information) :
        type(type),
        children {nullptr, nullptr, nullptr},
        information(information),
        token(nullptr),
        value(0)
{

}

Node::Node(NodeType type, Node *n1, Information *information) :
        type(type),
        children {n1, nullptr, nullptr},
        information(information),
        token(nullptr),
        value(0)
{

}

Node::Node(NodeType type, Information *information, Node *n1, Node *n2) :
        type(type),
        children {n1, n2, nullptr},
        information(information),
        token(nullptr),
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

Node::Node(NodeType type, unsigned intValue) :
        type(type),
        children {nullptr, nullptr, nullptr},
        information(nullptr),
        token(nullptr),
        value(intValue)
{

}

Node::Node(NodeType type, Token *token) :
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

    if (token != nullptr)
        delete token;
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


