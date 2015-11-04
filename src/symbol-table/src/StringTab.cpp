//
// Created by tim on 04.11.15.
//

#include <string.h>
#include "../headers/StringTab.h"


char* StringTab::insert(char* lexem, int size){
    char* tmp = this->freeP;
    if (size < this->freeSpace) {
        memcpy(this->freeP, lexem, size + 1);
        this->freeP[size] = '\0';
        this->freeP += size + 1;
        this->freeSpace -= size + 1;
    } else {
        //TODO: Implement
    }
    return tmp;
}
