
#include "../include/SymbolTable.h"

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "../../utils/include/colormod.h"

using namespace std;

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);

void comp(char * msg, char * str1, char * str2, bool expected);
void comp(char * msg, unsigned int result,unsigned int expectedValue, bool expected);
void comp(char * msg, Information * info1, Information * info2, bool expected);


int main( int argc, char **argv )
{
    cout << "====================================" << endl;
    cout << "==          Hash Tests           ===" << endl;
    cout << "====================================" << endl;

    SymbolTable* symbolTable = new SymbolTable();

    char test[] = "test";
    char test2[] = "test2";
    char test3[] = "test";

    comp((char *) "Test 1: Compare equal Hashs", symbolTable->hash(test), symbolTable->hash(test3), true);
    comp((char *) "Test 2: Compare non equal Hashs", symbolTable->hash(test), symbolTable->hash(test2), false);
    cout << endl << endl;


    cout << "====================================" << endl;
    cout << "==      Symbol Table Tests       ===" << endl;
    cout << "====================================" << endl;

    Information* info1 = symbolTable->insert("test", Token::TokenType::IDENTIFIER);
    Information* info2 = symbolTable->insert("test", Token::TokenType::IDENTIFIER);
    Information* info3 = symbolTable->insert("test2", Token::TokenType::IDENTIFIER);
    comp((char *) "Test 1: Compare equal lexems", info1, info2, true);
    comp((char *) "Test 2: Compare non equal lexems", info2, info3, false);
    comp((char *) "Test 3: Table contains 2 entries", symbolTable->getNumEntries(), 2, true);

    Information* info4 = symbolTable->insert("test3", Token::TokenType::IDENTIFIER);
    comp((char *) "Test 4: Table contains 3 entries", symbolTable->getNumEntries(), 3, true);


    int numEntriesBefore = symbolTable->getNumEntries();
    char buffer[6];
    for(int i = 0; i < 10000; i++) {
        sprintf(buffer,"%d",i);
        symbolTable->insert(buffer, Token::TokenType::IDENTIFIER);
    }
    int numEntriesAfter = symbolTable->getNumEntries();
    comp((char *) "Test 5: 10.000 new entries in SymbolTable", numEntriesAfter - numEntriesBefore, 10000, true);
    //symbolTable->dumpSymbolDistribution();


    cout << endl << endl;


    cout << "====================================" << endl;
    cout << "==     String Table Tests        ===" << endl;
    cout << "====================================" << endl;

    StringTab* stringTab = new StringTab();

    char c1[] = "tim";
    char* str1 = stringTab->insert(c1, 3);
    comp((char *) "Test 1", c1, str1, true);

    char c2[] = "essig";
    char* str2 = stringTab->insert(c2, 5);
    comp((char *) "Test 2", c2, str2, true);

    char c3[] = "essig12";
    char* str3 = stringTab->insert(c3, 5); // Wrong size, returned string should be trimmed by two characters
    comp((char *) "Test 3", c3, str3, false);

    for(int i=0; i < 10000; i++) {
        stringTab->insert("test", 4);
    }
    cout << "10.000 elements test:" << endl << green << "\t [OK]" << def << endl; //At least the app didn't crash after 10k inserts

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
 * @param result
 * @param expectedValue
 * @param expected
 */
void comp(char * msg, unsigned int result, unsigned int expectedValue, bool expected) {

    if((result == expectedValue) == expected) {
        cout << msg << ": " << endl << green << "\t [OK]" << def << endl;
    } else {
        cout << msg << ": " << endl << red << "\t[FAIL]" << def << "Expected: " << expectedValue << " got: " << result << endl;
    }
}


void comp(char * msg, Information* info1, Information* info2, bool expected) {
    bool result = info1 == info2;

    if(result == expected) {
        cout << msg << ": " << endl << green << "\t [OK]" << def << endl;
    } else {
        cout << msg << ": " << endl << red << "\t[FAIL]" << def << endl;
    }
}