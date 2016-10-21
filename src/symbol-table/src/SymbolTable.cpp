/**
 * SymbolTable.cpp
 */

#include "../headers/SymbolTable.h"
#include "../headers/SymbolTableEntry.h"


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
    insert("while", TType::ERROR_TYPE);
    //....
    //TODO: Should this be done by the scanner?
}

/**
 *
 */
Information* SymbolTable::insert(char const *lexem, TType type) {
    // 1. Check if lexem is already in SymTab
    // 2. If not insert and return Information
    // 3. If yes, get Information and return

    unsigned int hash = this->hash(lexem);


    if(symTabEntries[hash] == nullptr) {
        Information* info = new Information(type, lexem);
        symTabEntries[hash] = new SymbolTableEntry(info);
        numEntries++;
        return info;
    } else {
        SymbolTableEntry* currentEntry = symTabEntries[hash];
        do {
            if(currentEntry->getInformation()->compareLex(lexem)) {
                return currentEntry->getInformation();
            } else {
                if (currentEntry->getNext() != nullptr) {
                    currentEntry = currentEntry->getNext();
                }
            }
        } while(currentEntry->getNext() != nullptr);

        //No lexem found
        Information* info = new Information(type, lexem);
        currentEntry->setNext(new SymbolTableEntry(info));
        numEntries++;
        return info;
    }


}

unsigned int SymbolTable::getNumEntries() const {
    return this->numEntries;
}



