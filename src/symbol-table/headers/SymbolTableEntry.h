//
// Created by tim on 04.11.15.
//

#ifndef HSKA_COMPILER_SYMBOLTABLEENTRY_H
#define HSKA_COMPILER_SYMBOLTABLEENTRY_H


#include "Information.h"

class SymbolTableEntry {

private:
    Information* information = nullptr;
    SymbolTableEntry* next = nullptr;

public:
    SymbolTableEntry(Information * information);

    void setNext(SymbolTableEntry* next);
    SymbolTableEntry* getNext() const;

    Information* getInformation() const;
};


#endif //HSKA_COMPILER_SYMBOLTABLEENTRY_H
