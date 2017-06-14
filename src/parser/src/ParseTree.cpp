//
// Created by tim on 02.01.17.
//

#include "../include/ParseTree.h"
#include <cstdlib>
#include <iostream>
#include "../../utils/include/colormod.h"
#include <iomanip>
#include <string>
#include "../../utils/include/utils.h"

ParseTree::ParseTree(Node* root) : root(root)
{
}

ParseTree::~ParseTree()
{
    delete root;
}

Node* ParseTree::getRoot() const
{
    return root;
}

void ParseTree::dumpTree() const
{
    root->dump();
}

bool ParseTree::typeCheck(Node* node)
{
    if (node == nullptr)
        return true;

    bool valid = true;

    switch (node->getNodeType())
    {
    case Prog:
        valid &= typeCheck(node->getDecls()) ;
        valid &= typeCheck(node->getStatements()) ;
        break;

    case Decls:
        valid &= typeCheck(node->getDecl()) ;
        valid &= typeCheck(node->getDecls()) ;
        break;

    case DeclArray:
        {
            auto array = node->getArray();
            valid &= typeCheck(array) ;
            auto name = node->getInformation()->getName();
            if (getType(name) != TI_NOTYPE)
            {
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "identifier already defined: \"", name, "\"");
                node->type = TI_ERROR;
                valid = false;
            }
            else
                addIdentifier(name, TI_INT_ARRAY);
        }
        break;

    case DeclIdent:
        {
            auto name = node->getInformation()->getName();
            if (getType(name) != TI_NOTYPE)
            {   
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "identifier already defined: \"", name, "\"");
                node->type = TI_ERROR;
                valid = false;
            }
            else
                addIdentifier(name, TI_INT);
        }
        break;

    case Array:
        {
            auto index = node->getIntValue();
            if (index > 0)
                node->type = TI_ARRAY;
            else
            {
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "invalid dimension: ", index);
                node->type = TI_ERROR;
                valid = false;
            }
        }
        break;

    case Statements:
        valid &= typeCheck(node->getStatement()) ;
        valid &= typeCheck(node->getStatements()) ;
        break;

    case StatementIdent:
        {
            auto exp = node->getExp();
            auto index = node->getIndex();
            valid &= typeCheck(exp) ;
            valid &= typeCheck(index) ;
            auto name = node->getInformation()->getName();
            auto type = getType(name);
            if (type == TI_NOTYPE)
            {
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "identifier not defined: \"", name, "\"");
                node->type = TI_ERROR;
                valid = false;
            }
            else if (!(exp->type == TI_INT && (
                type == TI_INT && index->type == TI_NOTYPE ||
                type == TI_INT_ARRAY && index->type == TI_ARRAY)))
            {
                error(exp->getToken()->getLine(), exp->getToken()->getColumn(), "cannot convert int (", exp->getToken()->getValue(), ") to array (\"", name, "\")");
                node->type = TI_ERROR;
                valid = false;
            }
        }
        break;

    case StatementWrite:
        valid &= typeCheck(node->getExp()) ;
        break;

    case StatementRead:
        {
            auto index = node->getIndex();
            auto type = getType(node->getInformation()->getName());
            valid &= typeCheck(node->getIndex()) ;
            if (type == TI_NOTYPE)
            {
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "identifier not defined: \"", node->getInformation()->getName(), "\"");
                node->type = TI_ERROR;
                valid = false;
            }
            else if (!(type == TI_INT && index->type == TI_NOTYPE ||
                type == TI_INT_ARRAY && index->type == TI_ARRAY))
            {
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "incompatible types: \"", node->getInformation()->getName(), "\"");
                node->type = TI_ERROR;
                valid = false;
            }
        }
        break;

    case StatementIf:
        {
            auto exp = node->getExp();
            valid &= typeCheck(exp) ;
            valid &= typeCheck(node->getIfStatement()) ;
            valid &= typeCheck(node->getElseStatement()) ;
            if (exp->type == TI_ERROR)
            {
                node->type = TI_ERROR;
                valid = false;
            }
        }
        break;

    case StatementWhile:
        {
            auto exp = node->getExp();
            valid &= typeCheck(exp) ;
            valid &= typeCheck(node->getStatement()) ;
            if (exp->type == TI_ERROR)
            {
                node->type = TI_ERROR;
                valid = false;
            }
        }
        break;

    case StatementBlock:
        valid &= typeCheck(node->getStatements()) ;
        break;

    case Exp:
        {
            auto exp2 = node->getExp2();
            auto op = node->getOp();
            valid &= typeCheck(exp2) ;
            valid &= typeCheck(op) ;
            if (op->type == TI_NOTYPE || exp2->type == op->type)
                node->type = exp2->type;
            else
            {
                node->type = TI_ERROR;
                valid = false;
            }
        }
        break;

    case Exp2:
        {
            auto exp = node->getExp();
            valid &= typeCheck(exp) ;
            node->type = exp->type;
        }
        break;

    case Exp2Ident:
        {
            auto index = node->getIndex();
            valid &= typeCheck(index) ;
            auto type = getType(node->getInformation()->getName());
            if (type == TI_NOTYPE)
            {
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "identifier not defined: \"", node->getInformation()->getName(), "\"");
                node->type = TI_ERROR;
                valid = false;
            }
            else if (type == TI_INT && index->type == TI_NOTYPE)
                node->type = type;
            else if (type == TI_INT_ARRAY && index->type == TI_ARRAY)
                node->type = TI_INT;
            else
            {
                error(node->getToken()->getLine(), node->getToken()->getColumn(), "no primitive type: \"", node->getInformation()->getName(), "\"");
                node->type = TI_ERROR;
                valid = false;
            }
        }
        break;

    case Exp2Int:
        node->type = TI_INT;
        break;

    case Exp2Minus:
        {
            auto exp2 = node->getExp2();
            valid &= typeCheck(exp2) ;
            node->type = exp2->type;
        }
        break;

    case Exp2Neg:
        {
            auto exp2 = node->getExp2();
            valid &= typeCheck(exp2) ;
            node->type = exp2->type == TI_INT ? TI_INT : TI_ERROR;
        }
        break;

    case Index:
        {
            auto exp = node->getExp();
            valid &= typeCheck(exp) ;
            valid &= typeCheck(node->getStatement()) ;
            valid &= typeCheck(exp) ;
            if (exp->type == TI_ERROR)
                node->type = TI_ERROR;
            else node->type = TI_ARRAY;
        }
        break;

    case OpExp:
        valid &= typeCheck(node->getOp()) ;
        valid &= typeCheck(node->getExp()) ;
        node->type = node->getExp()->type;
        break;

    case Op:
        switch (node->getToken()->getType())
        {
        case Token::PLUS:
            node->type = TI_OP_PLUS;
            break;

        case Token::MINUS:
            node->type = TI_OP_MINUS;
            break;

        case Token::STAR:
            node->type = TI_OP_MULTIPLICATION;
            break;

        case Token::COLON:
            node->type = TI_OP_DIVISION;
            break;

        case Token::GREATER:
            node->type = TI_OP_GREATER;
            break;

        case Token::LESS:
            node->type = TI_OP_LESS;
            break;

        case Token::EQUAL:
            node->type = TI_OP_EQUAL;
            break;

        case Token::UNEQUAL:
            node->type = TI_OP_UNEQUAL;
            break;

        case Token::AND:
            node->type = TI_OP_AND;
            break;

        default:
            error(node->getToken()->getLine(), node->getToken()->getColumn(), "unknown operation");
            valid = false;
            break;
        }
        break;

    case Nil:
        break;

    default:
        error(node->getToken()->getLine(), node->getToken()->getColumn(), "unknown type");
    }
      
    return valid;
}

void ParseTree::addIdentifier(const char* name, TypeInfo type)
{
    identifiers[identifierCount] = {name, type};
    identifierCount++;
}

TypeInfo ParseTree::getType(const char* identifier) const
{
    for (int i = 0; i < identifierCount; i++)
    {
        if (identifiers[i].name == identifier)
            return identifiers[i].type;
    }

    return TI_NOTYPE;
}
