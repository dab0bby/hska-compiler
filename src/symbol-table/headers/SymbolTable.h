/**
 * SymbolTable.h
 */
#include "../headers/StringTab.h"

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_



class SymbolTable
{
private:
    StringTab* stringTab;



public:
    SymbolTable();
    virtual ~SymbolTable();

    void initSymbols();

    int hash(char* lexem);

};

#endif /* SYMBOLTABLE_H_ */
