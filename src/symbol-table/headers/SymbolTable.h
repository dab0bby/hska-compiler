/**
 * SymbolTable.h
 */
#include "../headers/StringTab.h"
#include "Information.h"
#include "../../scanner/headers/Token.h"

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_


class SymbolTableEntry;

class SymbolTable
{
private:
    StringTab* stringTab;



public:
    SymbolTable();
    virtual ~SymbolTable();

    void initSymbols();

    int hash(char* lexem);

    SymbolTableEntry* insert(char const *lexem, TType type);
    Information lookup(SymbolTableEntry* key);

};

#endif /* SYMBOLTABLE_H_ */
