//
// Created by tim on 04.11.15.
//

#include "../include/SymbolTableEntry.h"

SymbolTableEntry::SymbolTableEntry(Information *information) : information(information) {

}

void SymbolTableEntry::setNext(SymbolTableEntry *next) {
    this->next = next;
}

SymbolTableEntry *SymbolTableEntry::getNext() const {
    return this->next;
}

Information *SymbolTableEntry::getInformation() const {
    return this->information;
}
