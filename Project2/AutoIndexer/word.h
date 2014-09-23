#include <iostream>
#include <fstream>
#include <cstring>
#ifndef WORD_H
#define WORD_H

using namespace std;

class Word {

private:
    char** words;  // pointer array that stores words
    int capacity;
    int wordIndex;

public:
    Word();
    ~Word();
    void getWordSize(char*);
    int getCapacity();
    void getWords(char*, char**);
    void sortWords(int, ostream&, char**);
    int getIndex();
    char* getPageNumbers(char*, int, char**);
};

#endif // WORD_H
