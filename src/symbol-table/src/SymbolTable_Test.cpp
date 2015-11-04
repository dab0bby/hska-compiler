#include "../headers/SymbolTable.h"

#include <iostream>

int main( int argc, char **argv )
{
    SymbolTable* symbolTable;

    symbolTable = new SymbolTable();

    char test[] = "test";
    char test2[] = "test2";
    std::cout << "Hash: " << symbolTable->hash(test) << std::endl;
    std::cout << "Hash: " << symbolTable->hash(test) << std::endl;
    std::cout << "Hash2: " << symbolTable->hash(test2) << std::endl;

}
