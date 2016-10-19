/**
 * SymbolTable.cpp
 */

#include "../headers/SymbolTable.h"
#include "../headers/SymbolTableEntry.h"

SymbolTable::SymbolTable()
{
    stringTab = new StringTab();
}

SymbolTable::~SymbolTable()
{

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

/**
 * Zur Vorbelegung der Symboltabelle mit Schlüsselworten
 */
void SymbolTable::initSymbols() {
    insert("while", TType::ERROR_TYPE);
    //....
}

/**
 *
 */
SymbolTableEntry* SymbolTable::insert(char const *lexem, TType type) {

}


/**
 *
 */
Information SymbolTable::lookup(SymbolTableEntry* key) {

}

