#include <iostream>
#include <fstream>
#include <cstring>
#include "word.h"

using namespace std;

Word::Word()
{
    int wordIndex = 10;
    int capacity = 10; // starts at 10 because no more than 10 free spaces
}

Word::~Word() {
    delete[] words;
}

// -- gets the size of the input file rather than using a resize funtion
// -- cuz aint nobody got time for dat
void Word::getWordSize(char * file) {
    ifstream fileA(file);

    char temp[100];

    // -- increases capacity by 1 for every token read in file
    while(fileA >> temp) {
        capacity++;
    }

    fileA.close();
}

// -- gets the capacity
int Word::getCapacity() {
    return capacity;
}

// -- assignes the words from file into an array to be used for sorting
void Word::getWords(char * f, char ** info) {
    int size = 0;
    char buffer[100];

    ifstream file(f);

    // reads in the file and assigns each token to a spot in info array
    while(file >> buffer) {
        info[size] = new char[strlen(buffer) + 1];
        strcpy(info[size], buffer);
        size++;
    }

    int numPage = 0;

    // -- determines how many tokens are taken up by page numbers
    for (int i = 0; i < size; i++) {
        if (*info[i] == '<' || *info[i] == '[')
           numPage++;
    }

    // -- assigns space for words array based on the size of the file minus
    // the tokens taken up by a page number
    words = new char*[size - numPage];

    wordIndex = 0;

    // -- stores each word in a space in the array 'words'
    for (int i = 0; i < size; i++) {
        if (*info[i] == '<' || *info[i] == '[') {
            // do nothing
        } else {
            words[wordIndex] = info[i];
            wordIndex++;
        }
    }

}

int Word::getIndex() {
    return wordIndex;
}

void Word::sortWords(int size, ostream &out, char** pages) {
    char* temp = new char[size];

    // -- sorting algorithm, organizes everything alphabetically
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(words[i], words[j]) < 0) {
                temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }

    // -- algorithm that eliminates repeating words
    for (int i = size - 1; i > 0; i--) {
        if (strcmp(words[i], words[i - 1]) == 0) {
            //do nothing
        } else {
            // -- if a letter has multiple words, this will display all of them
            if (strncmp(words[i], words[i - 1], 1) == 0) {
                out << "[" << *words[i] << "]"<< endl;
                out << words[i] << " " << getPageNumbers(words[i], size, pages) << endl;
                out << words[i - 1] << " " << getPageNumbers(words[i - 1], size, pages) << endl;
                i--;
            } else {
                out << "[" << *words[i] << "]"<< endl;
                out << words[i] << " " << getPageNumbers(words[i], size, pages) << endl;
            }
        }
    }
}

char* Word::getPageNumbers(char* word, int size, char** pages) {
    // implement page algorithm


    return pages[1];
}



















