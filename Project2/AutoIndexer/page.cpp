#include <iostream>
#include <fstream>
#include <cstring>
#include "page.h"

using namespace std;

Page::Page()
{
    capacity = 10;  // starting capacity for index. Starts at 10
    int pageIndex = 0;
}

int Page::getCapacity() {
    return capacity;
}

// -- function reads in file from command line and increments capacity
//  in order to find the file size and later assign it to the info array
// -- NOTE:  I used this instead of a resize function
void Page::getFileSize(char* file) {

    ifstream tempf(file);
    char temp[100];

    // -- increases capacity by 1 everytime a word is read
    while(tempf >> temp) {
        capacity++;
    }

    tempf.close();
}

// -- function that assigns page numbers to an array from info
// will also determine the size of the pages array
void Page::getInfo(char * file, char** info) {
    int size = 0;
    char buffer[100];

    ifstream f(file); // read in file second time to assign info

    // -- reads in file
    while(f >> buffer) {
        info[size] = new char[strlen(buffer) + 1];
        strcpy(info[size], buffer);
        size++;
    }

    // -- searches "info" and increments page index everytime there is a page number
    for (int i = 0; i < size; i++) {
        if (*info[i] == '<') {
            pageIndex++;
        }
    }

    // -- initiate pages array with correct size
    pages = new char*[pageIndex];

    int index = 0;

    // -- stores the page numbers in pages from info
    for (int i = 0; i < size; i++) {
        if (*info[i] == '<') {
            pages[index] = info[i];
            index++;
        }
    }

    f.close();

}



void Page::getPage() {
    cout << "got page" << endl;
}

Page::~Page() {
    //delete[] words;
    delete[] pages;
}
