//
// Created by tim on 02.01.17.
//

#include "../include/ParseTree.h"

ParseTree::ParseTree(Node *root) : root(root)
{
}

ParseTree::~ParseTree()
{
    delete root;
}

Node *ParseTree::getRoot() const
{
    return root;
}

void ParseTree::dumpTree() const
{
    root->dump();
}

bool ParseTree::typeCheck(Node* node) const
{
    return true;
}