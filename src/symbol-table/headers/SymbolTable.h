/**
 * SymbolTable.h
 */
#include "../headers/StringTab.h"
#include "Information.h"
#include "../../scanner/include/Token.h"

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#define TABLE_SIZE 256

class SymbolTableEntry;

class SymbolTable
{
private:
    StringTab* stringTab;
    SymbolTableEntry* symTabEntries[TABLE_SIZE];
    unsigned int numEntries = 0;

    int countNumEntries(int hast) const;

public:
    SymbolTable();
    virtual ~SymbolTable();

    void initSymbols();

    unsigned int hash(char const* lexem);

    Information* insert(char const *lexem, TType type);

    unsigned int getNumEntries() const;

    void dumpSymbolDistribution() const;


};

#endif /* SYMBOLTABLE_H_ */
