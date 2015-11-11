/**
 * SymbolTable.h
 */
#include "../headers/StringTab.h"
#include "Information.h"

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

    //Key insert(char* lexem);
    //Information lookup(Key key);

};

#endif /* SYMBOLTABLE_H_ */
