//
// Created by tim on 02.01.17.
//

#ifndef HSKA_COMPILER_NODE_H
#define HSKA_COMPILER_NODE_H

#include "../../symbol-table/include/Information.h"

enum NodeType {
    Prog,
    Decls,
    DeclArray,
    DeclIdent,
    Array,
    Statements,
    StatementIdent,
    StatementWrite,
    StatementRead,
    StatementIf,
    StatementWhile,
    StatementBlock,
    Exp,
    Exp2,
    Exp2Ident,
    Exp2Int,
    Exp2Minus,
    Exp2Neg,
    Index,
    OpExp,
    Op,
    Nil,
};

class Node {

public:
    // Index, Exp2, Exp2Minus, Exp2Neg, StatementWrite, StatementBlock
    explicit Node(NodeType type, Node *n1);
    // Prog, Decls, OpExp, Statements, StatementWhile
    explicit Node(NodeType type, Node *n1, Node *n2);
    // StatementIf
    explicit Node(NodeType type, Node *n1, Node *n2, Node *n3);
    // DeclIdent
    explicit Node(NodeType type, Information *information);
    // DeclArray, Exp2Ident, StatementRead
    explicit Node(NodeType type, Node *n1, Information *information);
    // StatementIdent
    explicit Node(NodeType type, Information *information, Node *n1, Node *n2);
    // Nil
    explicit Node(NodeType type);
    // Array, Exp2Int
    explicit Node(NodeType type, unsigned intValue);
    // Op
    explicit Node(NodeType type, Token *token);

    ~Node();

    void dump();

    const char* typeToString(NodeType type) const;

private:
    Node* n1;
    Node* n2;
    Node* n3;
    Information* information;
    Token* token;
    NodeType type;
    //TODO: Type(Int|IntArray|NoType)
    unsigned int value; //Only positive
    void dump(int i);
};


#endif //HSKA_COMPILER_NODE_H
