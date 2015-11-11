//
// Created by tim on 04.11.15.
//

#ifndef HSKA_COMPILER_STRINGTAB_H
#define HSKA_COMPILER_STRINGTAB_H


#include "StringTabNode.h"

class StringTab {

private:
    char* freeP; //Pointer auf Anfang des freien Bereichs
    int freeSpace;

    StringTabEntry* first = nullptr;

public:
    StringTab();
    char* insert(char* lexem, int size);
};


#endif //HSKA_COMPILER_STRINGTAB_H
