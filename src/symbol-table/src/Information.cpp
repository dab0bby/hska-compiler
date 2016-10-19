//
// Created by tim on 04.11.15.
//

#include "../headers/Information.h"

Information::Information(TType type) : type(type) {

}


TType Information::getType() {
    return this->type;
}