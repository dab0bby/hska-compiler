/**
 * @author   Bob
 * @date     14/01/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include <math.h>
#include <string.h>

#include "../include/CodeGenerator.h"


CodeGenerator::CodeGenerator()
{
}


void CodeGenerator::generate(const Node* node, std::ostream& out)
{
    if (node == nullptr)
        return;

   switch (node->getNodeType())
   {
       // PROG
        case NodeType::Prog:  // DECLS STATEMENTS
            generate(node->getDecls(), out);        // DECLS
            generate(node->getStatements(), out);   // STATEMENTS
            out << "NOP\n";                         // NOP
            out << "STP\n";                         // Program exit
            break;

        // DECLS
        case NodeType::Decls: // DECL; DECLS | e
            generate(node->getDecl(), out);     // DECL
            generate(node->getDecls(), out);    // DECLS
            break;

        // DECL
        case NodeType::DeclArray: // int ARRAY identifier
            out << "DS $" << node->getInformation()->getName();     // Allocate memory and set variable name
            generate(node->getArray(), out);                        // ARRAY (size of array)
            break;

        // identifier
        case NodeType::DeclIdent: // int identifier
            out << "DS $" << node->getInformation()->getName() << " 1\n";  // Allocate memory and set variable name. 1 because its an 'empty' integer
            break;

        // ARRAY
        case NodeType::Array: // [integer] | e
            out << " " << node->getIntValue() << "\n"; // Size of array
            break;

        // STATEMENTS
        case NodeType::Statements:
            generate(node->getStatement(), out);    // STATEMENT
            generate(node->getStatements(), out);   // STATEMENTS
            break;

        // identifier
        case NodeType::StatementIdent:
            generate(node->getExp(), out);                                  // EXP (generate code for rvalue first)
            out << "LA $" << node->getInformation()->getName() << "\n";     // Load address
            generate(node->getIndex(), out);                                // check if its an index of an array
            out << "STR\n";
            break;

        // write
        case NodeType::StatementWrite:
            generate(node->getExp(), out);  // EXP
            out << "PRI\n";                 // Print value
            break;

        // read
        case NodeType::StatementRead:
            out << "REA\n";                                             // Read value
            out << "LA $" << node->getInformation()->getName() << "\n"; // Load adress of given identifier
            generate(node->getIndex(), out);                            // check if its an index of an array
            out << "STR\n";                                             // Save value
            break;

        // Code block
        case NodeType::StatementBlock:
            generate(node->getStatements(), out);   // STATEMENTS
            break;

        // if
        case NodeType::StatementIf:
        {
            generate(node->getExp(), out);              // EXP
            auto label1 = _createLabel();
            out << "JIN #" << label1 << "\n";           // Jump to label1
            generate(node->getIfStatement(), out);      // Generate if STATEMENT
            auto label2 = _createLabel();
            out << "JMP #" << label2 << "\n";           // Jump to label2
            out << "#" << label1 << " NOP\n";           // Content of label1
            generate(node->getElseStatement(), out);    // Generate else STATEMENT
            out << "#" << label2 << " NOP\n";           // Content of label2 (end of if statement)
            delete[] label2;
            delete[] label1;
            break;
        }

        // while
        case NodeType::StatementWhile:
        {
            auto label1 = _createLabel();
            out << "#" << label1 << " NOP\n";       // Content of label1
            generate(node->getExp(), out);          // EXP
            auto label2 = _createLabel();
            out << "JIN #" << label2 << "\n";       // Jump to label2
            generate(node->getStatement(), out);    // while STATEMENT
            out << "JMP #" << label1 << "\n";       // Jump back to label1
            out << "#" << label2 << " NOP\n";       // Content of label2 (End of while statement)
            delete[] label2;
            delete[] label1;
            break;
        }

        // EXP
        case NodeType::Exp:
        {
            const auto expType = node->getOp()->type;   // Typ of EXP

            if (expType == TypeInfo::TI_NOTYPE)
                generate(node->getExp2(), out);     // EXP2
            else
            {
                const auto op = node->getOp()->getOp()->getToken()->getType();

                if (op == Token::TokenType::GREATER)
                {
                    generate(node->getOp(), out);   // OP_EXP
                    generate(node->getExp2(), out); // EXP2
                    out << "LES\n";
                }
                else if (op == Token::TokenType::UNEQUAL)
                {
                    generate(node->getExp2(), out); // EXP2
                    generate(node->getOp(), out);   // OP_EXP
                    out << "NOT\n";
                }
                else
                {
                    generate(node->getExp2(), out); // EXP2
                    generate(node->getOp(), out);   // OP_EXP
                }
            }

            break;
        }

        // EXP2
        case NodeType::Exp2:
            generate(node->getExp(), out);  // EXP
            break;

        // EXP2 ident
        case NodeType::Exp2Ident:
            out << "LA $" << node->getInformation()->getName() << "\n";     // load address of identiefier
            generate(node->getIndex(), out);    // INDEX
            out << "LV\n";  // Load value
            break;

        // EXP2 integer
        case NodeType::Exp2Int:
            out << "LC " << node->getIntValue() << "\n";    // load constant value
            break;

        // EXP2 minus
        case NodeType::Exp2Minus:
            out << "LC 0\n";    // Load constant value 0
            generate(node->getExp2(), out); // EXP2
            out << "SUB\n";     // Substract values
            break;

        // EXP2 negate
        case NodeType::Exp2Neg:
            generate(node->getExp2(), out); // EXP2
            out << "NOT\n"; // Negate integer
            break;

        // INDEX
        case NodeType::Index:
            generate(node->getExp(), out);  // EXP
            out << "ADD\n"; // add those values
            break;

        // OP_EXP
        case NodeType::OpExp:
            generate(node->getExp(), out);  // EXP
            generate(node->getOp(), out);   // OP
            break;

        // OP
        case NodeType::Op:
        {
            switch(node->getToken()->getType())
            {
                // +
                case Token::TokenType::PLUS:
                    out << "ADD\n";
                    break;

                // -
                case Token::TokenType::MINUS:
                    out << "SUB\n";
                    break;

                // *
                case Token::TokenType::STAR:
                    out << "MUL\n";
                    break;

                // :
                case Token::TokenType::COLON:
                    out << "DIV\n";
                    break;

                // <
                case Token::TokenType::LESS:
                    out << "LES\n";
                    break;

                // >
                case Token::TokenType::GREATER:
                    // EXP rule applies here
                    break;

                // =
                case Token::TokenType::EQUAL:
                    out << "EQU\n";
                    break;

                // =:=
                case Token::TokenType::UNEQUAL:
                    out << "EQU\n"; // And rule EXP applies here
                    break;

                // &&
                case Token::TokenType::AND:
                    out << "AND\n";
                    break;

                default:
                    break;
            }

            break;
        }

        // e
        case NodeType::Nil:   // Empty node
            break;

        default:
            break;
   }
}


/**
 * \brief   Create a unique label
 */
const char* CodeGenerator::_createLabel()
{
    const int digitCount = _labelCount > 0 ? log10(_labelCount) + 1 : 1;
    const auto size = strlen("lbl") + digitCount;
    auto label = new char[size + 1];

    // Fill label
    sprintf(label, "lbl%u", _labelCount);

    // Terminate label
    label[size] = 0;

    // Increment label count
    _labelCount++;
    return label;
}


CodeGenerator::~CodeGenerator()
{
}
