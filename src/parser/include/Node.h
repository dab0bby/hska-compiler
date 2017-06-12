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

enum TypeInfo
{
	TI_NOTYPE,
	TI_ERROR,
	TI_INT,
	TI_ARRAY,
	TI_INT_ARRAY,
	TI_OP_PLUS,
	TI_OP_MINUS,
	TI_OP_MULTIPLICATION,
	TI_OP_DIVISION,
	TI_OP_LESS,
	TI_OP_GREATER,
	TI_OP_EQUAL,
	TI_OP_UNEQUAL,
	TI_OP_AND,
};

class Node {

public:
    //Static factory methods
    static Node* makeStatementWrite(Node* exp);
    static Node* makeStatementBlock(Node* statements);
    static Node* makeIndex(Node* exp);
    static Node* makeType(Node* exp);
    static Node* makeExp2Minus(Node* exp2);
    static Node* makeExp2Neg(Node* exp2);

    static Node* makeProg(Node* decls, Node* statements);
    static Node* makeDecls(Node* decl, Node* decls);
    static Node* makeStatements(Node* statement, Node* statements);
    static Node* makeStatementWhile(Node* exp, Node* statement);
    static Node* makeExp(Node* exp2, Node* op);
    static Node* makeOpExp(Node* op, Node* exp);

    static Node* makeStatementIf(Node* exp, Node* ifStmt, Node* elseStmt);

    static Node* makeDeclIdent(Information* ident);

    static Node* makeDeclArray(Node* arr, Information* ident);
    static Node* makeStatementRead(Node* idx, Information* ident);
    static Node* makeExp2Ident(Node* idx, Information* ident);

    static Node* makeStatementIdent(Information* ident, Node* idx, Node* exp);

    static Node* makeArray(unsigned int size);
    static Node* makeExp2Int(unsigned int i);

    static Node* makeOp(Token* token);

    static Node* makeNil();


    /**
     * Destructor
     */
    ~Node();

    /**
     * Valid for Decls-Node
     * @return A Decl-Node
     */
    Node* getDecl() const;

    /**
     * Valid for Prog-Node and  Decls-Node
     * @return A Decls-Node
     */
    Node* getDecls() const;

    /**
     * Valid for Statements-Node and StatementWhile-Node
     * @return A Statement-Node
     */
    Node* getStatement() const;

    /**
     * Valid for Statements-Node, StatementsBlock-Node and Prog-Node
     * @return
     */
    Node* getStatements() const;

    /**
     * Valid for DeclArray-Node
     * @return A Array-Node
     */
    Node* getArray() const;

    /**
     * Valid for StatementIdent-Node, StatementWrite-Node, StatementIf-Node, StatementWhile-Node, Index-Node, Exp2-Node and OpExp-Node
     * @return A Exp-Node
     */
    Node* getExp() const;

    /**
     * Valid for Exp-Node, Exp2Neg-Node and Exp2Minus-Node
     * @return A Exp2-Node
     */
    Node* getExp2() const;


    /**
     * Valid for Exp-Node and OpExp-Node
     * @return A Op-Node
     */
    Node* getOp() const;

    /**
     * Valid for StatementIdent-Node, StatementRead-Node and Exp2Ident-Node
     * @return A Index-Node
     */
    Node* getIndex() const;

    /**
     * Valid for StatementIf-Node
     * @return A Statement-Node
     */
    Node* getIfStatement() const;

    /**
     * Valid for StatementIf-Node
     * @return A Statement-Node
     */
    Node* getElseStatement() const;

    /**
     * Valid for DeclArray-Node, DeclIdent-Node, StatementIdent-Node, StatementRead-Node and Exp2Ident-Node
     * @return The Information of the Node
     */
    Information* getInformation() const;

    /**
     * Valid for Array-Node and Exp2Int-Node
     * @return The integer Value of the Node
     */
    unsigned int getIntValue() const;

    /**
     * Valid for Op-Node
     * @return The Token of the Node
     */
    Token* getToken() const;

    /**
     * Prints the structure of the node as a tree
     */
    void dump();

	NodeType getNodeType() const;

	TypeInfo type = TI_NOTYPE;

    /**
     * Returns the Name of the given Type as a char array
     * @param type
     * @return
     */
    static const char* typeToString(NodeType type);

private:
    Node* children[3];
    Information* information;
    Token* token;
    NodeType nodeType;
    unsigned int value;


    void dump(int i);
    void error(const char* functionName) const;

    /**
     * Constructor for Index-Node, Exp2-Node, Exp2Minus-Node, StatementWrite-Node and StatementBlock-Node
     */
    explicit Node(NodeType type, Node *n1);

    /**
     * Constructor for Prog-Node, Decls-Node, OpExp-Node, Statements-Node, StatementWhile-Node
     */
    explicit Node(NodeType type, Node *n1, Node *n2);

    /**
     * Constructor for StatementIf-Node
     */
    explicit Node(NodeType type, Node *n1, Node *n2, Node *n3);

    /**
     * Constructor for DeclInt-Node
     */
    explicit Node(NodeType type, Information *information);

    /**
     * Constructor for StatementIdent-Node
     */
    explicit Node(NodeType type, Information *information, Node *n1, Node *n2);

    /**
     * Constructor for Array-Node and Exp2Int-Node
     */
    explicit Node(NodeType type, unsigned int intValue);

    /**
     * Constructor for Nil-Node
     */
    explicit Node(NodeType type);

    /**
     * Constructor for DeclArray-Node, Exp2Ident-Node, StatementRead-Node
     */
    explicit Node(NodeType type, Node *n1, Information *information);

    /**
     * Constructor for Op-Node
     */
    explicit Node(NodeType type, Token *token);
};

#endif //HSKA_COMPILER_NODE_H
