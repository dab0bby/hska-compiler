//
// Created by tim on 02.01.17.
//

#include "../include/Node.h"

#include <iostream>
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


