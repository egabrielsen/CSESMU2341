// Erik Gabrielsen
// Project 2 - AutoIndexer
// September 22, 2014

#include <iostream>
#include <fstream>

using namespace std;

void resize(char**& d, int& cap);
void readFile(char *, char**, int**);
void checkCommandLine(int);

int main(int argc, char* argv[]) {
    checkCommandLine(argc);

    int capacity = 10; // start the array off with 10 free spaces and add more space as file is read
    char* file = argv[1];
    char** words = new char*[capacity];
    int** pages = new int*[capacity];

    readFile(file, words, pages);

    cout << "Hello" << endl;
    return 0;
}

void readFile(char * f, char ** w, int** p) {
    ifstream file(f);

    if (!file.is_open()) {
        cout << "File not opened..." << endl;
    }

    //read in file

    file.close();
}

void checkCommandLine(int a) {
    if (a != 3)
        cout <<  "Invalid number of Arguments\nExpected ./a.out <input.txt> <output.txt>" << endl;
}

void resize(char **&d, int &cap) {
    char** temp = new char*[cap + 10];
    for (int i = 0; i < cap; i++) {
        temp[i] = d[i];
    }
    delete[] d;
    d = temp;
    cap += 10;
}
