
#include "../headers/SymbolTable.h"

#include <iostream>
#include "../../utils/header/colormod.h"

using namespace std;

int main( int argc, char **argv )
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier def(Color::FG_DEFAULT);
    
    //Test SymTable
    SymbolTable* symbolTable;

    symbolTable = new SymbolTable();

    char test[] = "test";
    char test3[] = "test";
    char test2[] = "test2";

    cout << "Hash Test 1(Equal Hash)" << endl;
    bool result = symbolTable->hash(test) == symbolTable->hash(test3);

    if(result) {
        cout << "Result: " << green << "\t[OK]" << def << endl;
    } else {
        cout << "Result: " << red << "\t[FAIL]" << def << endl;
    }

    cout << "Hash Test 2(Non equal Hash)" << endl;
    result = symbolTable->hash(test) != symbolTable->hash(test2);

    if(result) {
        cout << "Result: " << green << "\t[OK]" << def << endl;
    } else {
        cout << "Result: " << red << "\t[FAIL]" << def << endl;
    }


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
