#include "sortingcompetition.h"
#include <iostream>
#include <cstring>
#include <ostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include "string.h"

using namespace std;

SortingCompetition::SortingCompetition() {
    fileCapacity = 0;
}

SortingCompetition::SortingCompetition(const string& inputFileName) {
    fileName = inputFileName;
    fileCapacity = 0;
}

void SortingCompetition::setFileName(const string& inputFileName) {

}

bool SortingCompetition::readData() {
    ifstream file(fileName);
    char temp[100];

    while (file >> temp) {
        fileCapacity++;
    }

    cout << "fileCapacity: " << fileCapacity << endl;

    file.close();

    ifstream file1(fileName);
    fileInfo = new char*[fileCapacity];
    char buffer[80];
    long size = 0;

    while (file1 >> buffer) {
        fileInfo[size] = new char[strlen(buffer) + 1];
        strcpy(fileInfo[size], buffer);
        size++;
    }

    file1.close();

    return true;
}

bool SortingCompetition::prepareData() {
    copyInfo = new char*[fileCapacity];

    for (int i = 0; i < fileCapacity; i++) {
        copyInfo[i] = new char[strlen(fileInfo[i]) + 1];
        strcpy(copyInfo[i], fileInfo[i]);
    }

    return true;
}

void SortingCompetition::sortData() {
   sizeSortingAlg(fileInfo, 0, fileCapacity - 1);
   for (int i = 0; i < fileCapacity; i++) {
       *copyInfo[i] = toupper(*copyInfo[i]);
   }
   alphabetize(copyInfo, 0, fileCapacity - 1);
}

void SortingCompetition::alphabetize(char ** words, long start, long end) {
    if (end - start < 2) {
        return;
    }

    long q = partitionA(words, start, end);
    alphabetize(words, start, q);
    alphabetize(words, q, end);
}

long SortingCompetition::partitionA(char** words, long p, long r) {
    char* x = words[p];
    char* y = words[(r - p) / 2 + p];
    char* z = words[r - 1];
    long i = p - 1;
    long j = r;

    if (((strcmp(y, x) > 0) && (strcmp(y, z) < 0)) || ((strcmp(y, z) > 0) && (strcmp(y, x) < 0))) {
        x = y;
    } else if (((strcmp(z, x) > 0) && (strcmp(z, y) < 0)) || ((strcmp(z, y) > 0) && (strcmp(z, x) < 0))) {
        x = z;
    }

    while (1) {
        do {
            j--;
        } while (strcmp(words[j], x) > 0);
        do {
            i++;
        } while (strcmp(words[i], x) < 0);
        if (i < j) {
            char* temp = words[i];
            words[i] = words[j];
            words[j] = temp;
        } else
            return j + 1;
    }
}

void SortingCompetition::sizeSortingAlg(char** words, long start, long end) {
    if (end - start < 2) {
        return;
    }

    long q = partition(words, start, end);
    sizeSortingAlg(words, start, q);
    sizeSortingAlg(words, q, end);
}

long SortingCompetition::partition(char** words, long p, long r) {
    int x = strlen(words[p]);
    int y = strlen(words[(r - p) / 2 + p]);
    int z = strlen(words[r - 1]);
    long i = p - 1;
    long j = r;

    if ((y > x && y < z) || (y > z && y < x)) {
        x = y;
    } else if ((z > x && z < y) || (z > y && z < x)) {
        x = z;
    }

    while (1) {
        do {
            j--;
        } while (strlen(words[j]) > x);
        do {
            i++;
        } while (strlen(words[i]) < x);
        if (i < j) {
            char* temp = words[i];
            words[i] = words[j];
            words[j] = temp;
        } else
            return j + 1;
    }

}

void SortingCompetition::outputData(const string& outputFileName) {
    ofstream output;
    output.open(outputFileName);
    output << "Sort Words by Size: \n" << endl;

    for (int i = 0; i < fileCapacity; i++) {
        output << fileInfo[i] << endl;
    }

    output << "Sort Words in Alphabetical Order: \n" << endl;

    for (int i = 0; i < fileCapacity; i++) {
        output << copyInfo[i] << endl;
    }
    output.close();
}

SortingCompetition::~SortingCompetition() {
    delete[] fileInfo;
    delete[] copyInfo;
}
