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
    bool typeCheck(Node* node);

private:
	void addIdentifier(const char* name, TypeInfo type);
	TypeInfo getType(const char* identifier) const;

	Node* root;
	int identifierCount = 0;

	struct IdentifierInfo
	{
		const char* name;
		TypeInfo type;
	} identifiers[5000];


};

#endif //HSKA_COMPILER_PARSETREE_H
