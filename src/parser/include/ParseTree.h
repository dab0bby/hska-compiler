//
// Created by tim on 02.01.17.
//

#ifndef HSKA_COMPILER_PARSETREE_H
#define HSKA_COMPILER_PARSETREE_H


#include "Node.h"

class ParseTree {

public:
    ParseTree(Node* root);
    ~ParseTree();

    Node* getRoot() const;
    void dumpTree() const;
    bool typeCheck(Node* node) const;
private:
    Node* root;


};


#endif //HSKA_COMPILER_PARSETREE_H
