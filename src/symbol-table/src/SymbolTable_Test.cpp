#include "../headers/SymbolTable.h"

#include <iostream>

using namespace std;

int main( int argc, char **argv )
{

    //Test SymTable
    SymbolTable* symbolTable;

    symbolTable = new SymbolTable();

    char test[] = "test";
    char test2[] = "test2";
    std::cout << "Hash: " << symbolTable->hash(test) << std::endl;
    std::cout << "Hash: " << symbolTable->hash(test) << std::endl;
    std::cout << "Hash2: " << symbolTable->hash(test2) << std::endl;


    //Test StringTab
    StringTab* stringTab = new StringTab();
    char c1[] = "tim";
    char* str1 = stringTab->insert(c1, 3);

    char c2[] = "essig";
    char* str2 = stringTab->insert(c2, 5);

    char c3[] = "essig12";
    char* str3 = stringTab->insert(c3, 7);

    std::cout << "Str1: " << str1 << endl;
    std::cout << "Str2: " << str2 << endl;
    std::cout << "Str3: " << str3 << endl;



}
