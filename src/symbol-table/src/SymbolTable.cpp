/**
 * SymbolTable.cpp
 */

#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"

#include <iostream>
#include <cstring>

using namespace std;


SymbolTable::SymbolTable()
{
    stringTab = new StringTab();

    //Necessary?
    for(int i=0; i < TABLE_SIZE; i++) {
        this->symTabEntries[i] = nullptr;
    }
}

SymbolTable::~SymbolTable()
{
    for(int i=0; i < TABLE_SIZE; i++) {
        if(this->symTabEntries[i] != nullptr) {
            SymbolTableEntry* entry = this->symTabEntries[i];
            while(entry != nullptr) {
                SymbolTableEntry* current = entry;
                entry = entry->getNext();
                delete current;
            }
        }
    }

    delete stringTab;
}

/**
 * Erzeugt einen Hash
 */
unsigned int SymbolTable::hash(char const* lexem) {
    unsigned int h = 0;

    while( *lexem != 0)
    {
        h = 31*h + *lexem;
        lexem++;
    }

    return h % TABLE_SIZE;
}

/**
 * Zur Vorbelegung der Symboltabelle mit Schlüsselworten
 */
void SymbolTable::initSymbols() {
    insert("while", Token::TokenType::ERROR);
    //....
    //TODO: Should this be done by the scanner?
}

/**
 *
 */
Information* SymbolTable::insert(char const *lexem, Token::TokenType type) {
    // 0. Copy Lexem in StringTable
    // 1. Check if lexem is already in SymTab
    // 2. If not insert and return Information
    // 3. If yes, get Information and return

    const char * internalLexem = stringTab->insert(lexem, strlen(lexem));

    unsigned int hash = this->hash(internalLexem);


    if(symTabEntries[hash] == nullptr) {
        Information* info = new Information(type, internalLexem);
        symTabEntries[hash] = new SymbolTableEntry(info);
        numEntries++;
        return info;
    } else {
        SymbolTableEntry* currentEntry = symTabEntries[hash];
        do {
            if(currentEntry->getInformation()->compareLex(internalLexem)) {
                return currentEntry->getInformation();
            } else {
                if (currentEntry->getNext() != nullptr) {
                    currentEntry = currentEntry->getNext();
                }
            }
        } while(currentEntry->getNext() != nullptr);

        //No lexem found
        Information* info = new Information(type, internalLexem);
        currentEntry->setNext(new SymbolTableEntry(info));
        numEntries++;
        return info;
    }


}

unsigned int SymbolTable::getNumEntries() const {
    return this->numEntries;
}


void SymbolTable::dumpSymbolDistribution() const {
    cout << "Num Entires per Hash" << endl;

    for(int i=0; i < TABLE_SIZE; i++) {
        cout << "Hash " << i << ": " << countNumEntries(i) << endl;
    }
}

int SymbolTable::countNumEntries( int hast) const {
    if(this->symTabEntries[hast] == nullptr)
        return 0;

    int num = 1;
    SymbolTableEntry* entry = this->symTabEntries[hast];
    while(entry->getNext() != nullptr) {
        entry = entry->getNext();
        num++;
    }

    return num;
}





