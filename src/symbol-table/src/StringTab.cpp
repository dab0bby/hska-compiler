//
// Created by tim on 04.11.15.
//

#include <string.h>
#include "../include/StringTab.h"

StringTab::StringTab() {

    first = new StringTabEntry();
    freeP = first->getVector();
    freeSpace = StringTabEntry::DEFAULT_SIZE;

}


StringTab::~StringTab() {
    StringTabEntry* current = first;
    while(current != nullptr) {
        StringTabEntry* next = current->getNext();
        delete current;
        current = next;
    }
}

/**
 * Insert the given lexem into the StringTab, returns a pointer to the stored string
 * @param lexem
 * @param size
 * @return
 */
const char* StringTab::insert(char const *lexem, int size) {
    char* tmp = this->freeP;
    if (size < this->freeSpace) {
        memcpy(this->freeP, lexem, size + 1);
        this->freeP[size] = '\0';
        this->freeP += size + 1;
        this->freeSpace -= size + 1;
    } else {
        StringTabEntry* newEntry = new StringTabEntry();
        freeP = newEntry->getVector();
        freeSpace = StringTabEntry::DEFAULT_SIZE;

        StringTabEntry* entry = first;
        while(entry->getNext()) {
            entry = entry->getNext();
        }
        entry->setNext(newEntry);

        tmp = freeP;
        memcpy(this->freeP, lexem, size + 1);
        this->freeP[size] = '\0';
        this->freeP += size + 1;
        this->freeSpace -= size + 1;
    }

    return tmp;
}


