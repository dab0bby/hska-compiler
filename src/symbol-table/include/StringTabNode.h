//
// Created by tim on 04.11.15.
//

#ifndef HSKA_COMPILER_STRINGTABENTRY_H
#define HSKA_COMPILER_STRINGTABENTRY_H


class StringTabEntry {

private:
    char* vector;
    StringTabEntry* next = nullptr;
public:
    StringTabEntry();
    char * getVector() const;
    StringTabEntry* getNext() const;
    void setNext(StringTabEntry* next);

    static const int DEFAULT_SIZE = 512;




};


#endif //HSKA_COMPILER_STRINGTABENTRY_H
