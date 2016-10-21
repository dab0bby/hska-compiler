
#include "../headers/SymbolTable.h"

#include <iostream>
#include <cstring>
#include "../../utils/header/colormod.h"

using namespace std;

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);

void comp(char * msg, char * str1, char * str2, bool expected);
void comp(char * msg, int num1, int num2, bool expected);


int main( int argc, char **argv )
{
    cout << "====================================" << endl;
    cout << "==      Hash Table Tests        ===" << endl;
    cout << "====================================" << endl;

    char test[] = "test";
    char test2[] = "test2";
    char test3[] = "test";

    SymbolTable* symbolTable = new SymbolTable();

    comp("Test 1: Equal Hash", symbolTable->hash(test), symbolTable->hash(test3), true);
    comp("Test 2: Non equal Hash", symbolTable->hash(test), symbolTable->hash(test2), false);


    cout << endl << endl;

    cout << "====================================" << endl;
    cout << "==     String Table Tests        ===" << endl;
    cout << "====================================" << endl;

    StringTab* stringTab = new StringTab();

    char c1[] = "tim";
    char* str1 = stringTab->insert(c1, 3);
    comp("Test 1", c1, str1, true);

    char c2[] = "essig";
    char* str2 = stringTab->insert(c2, 5);
    comp("Test 2", c2, str2, true);

    char c3[] = "essig12";
    char* str3 = stringTab->insert(c3, 5); // Wrong size, returned string should be trimmed by two characters
    comp("Test 3", c3, str3, false);

}

/**
 * Check if the two strings are equal but do not have the same address
 * @param msg
 * @param str1
 * @param str2
 */
void comp(char * msg, char * str1, char * str2, bool expected) {
    bool result = strcmp(str1, str2) == 0 && str1 != str2;

    if(result == expected) {
        cout << msg << ": " << endl << green << "\t [OK]" << def << endl;
    } else {
        cout << msg << ": " << endl << red << "\t[FAIL]" << def << endl;
    }
}

/**
 * Check if the two integers are equal
 * @param msg
 * @param num1
 * @param num2
 * @param expected
 */
void comp(char * msg, int num1, int num2, bool expected) {
    bool result = num1 == num2;

    if(result == expected) {
        cout << msg << ": " << endl << green << "\t [OK]" << def << endl;
    } else {
        cout << msg << ": " << endl << red << "\t[FAIL]" << def << endl;
    }
}