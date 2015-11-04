/**
 * SymbolTable.cpp
 */

#include "../headers/SymbolTable.h"

SymbolTable::SymbolTable()
{
    // TODO Auto-generated constructor stub

}

SymbolTable::~SymbolTable()
{
    // TODO Auto-generated destructor stub
}

/**
 * Erzeugt einen Hash 8 Bit Hash
 */
int SymbolTable::hash(char* lexem) {
    unsigned char h = 0;

    while( *lexem != 0)
    {
        h = 31*h + *lexem;
        lexem++;
    }

    return h;
}

void SymbolTable::initSymbols() {
//    insert("while", TokenWhile);
    //....
}
