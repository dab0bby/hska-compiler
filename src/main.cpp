#include "symbol-table/headers/SymbolTable.h"
#include "scanner/headers/Scanner.h"

#include <iostream>

using namespace std;

int main( int argc, char **argv )
{
    std::cout << "HsKA Compiler" << std::endl;

    SymbolTable* symbolTable = new SymbolTable();
    Scanner* scanner = new Scanner( argv[ 1 ], symbolTable );
}
