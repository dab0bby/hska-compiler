//
// Created by tim on 04.11.15.
//

#include <stdlib.h>
#include <malloc.h>
#include "../headers/StringTabNode.h"

StringTabEntry::StringTabEntry() {
    vector = (char*) malloc( DEFAULT_SIZE * sizeof(char));
}

char* StringTabEntry::getVector() const {
    return vector;
}


StringTabEntry* StringTabEntry::getNext() const {
    return next;
}


void StringTabEntry::setNext(StringTabEntry* next) {
    this->next = next;
}
