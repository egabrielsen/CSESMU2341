// Erik Gabrielsen
// Project 2 - AutoIndexer
// September 22, 2014

#include <iostream>
#include <fstream>
#include <cstring>
#include "page.h"
#include "page.cpp"
#include "word.h"
#include "word.cpp"

using namespace std;

// -- declare functions
void checkCommandLine(int);

int main(int argc, char* argv[]) {

    checkCommandLine(argc); // check number of arguments in command line
    Page *page = new Page(); // create a page object that will store page numbers
    page->getFileSize(argv[1]);  // get the file size of the input
    char** information = new char*[page->getCapacity()]; // create an array that will store all elements in input
    page->getInfo(argv[1], information); // gets the page numbers from info

    Word *word = new Word(); // create a word object that stores all words
    word->getWordSize(argv[1]); // get the file size of input for word
    word->getWords(argv[1], information); // gets the words and stores into an array
    ofstream output;
    output.open(argv[2]);
    word->sortWords(word->getIndex(), output);
    output.close();

    //Deconstruction
    word->~Word();
    delete[] *information;
    page->~Page();

    return 0;
}

// -- Fuction checks the number of arguments in command line
void checkCommandLine(int a) {
    if (a != 3)
        cout <<  "Invalid number of Arguments\nExpected ./a.out <input.txt> <output.txt>" << endl;
}


