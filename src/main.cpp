#include "symbol-table/include/SymbolTable.h"
#include "scanner/include/Scanner.h"

#include <iostream>


using namespace std;


int main(int argc, char **argv)
{
    std::cout << "HsKA Compiler" << std::endl;

    SymbolTable* symbolTable = new SymbolTable();
    Scanner scanner(argv[1], symbolTable);
}
