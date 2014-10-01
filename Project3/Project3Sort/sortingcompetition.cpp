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
    int size = 0;

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
   sortingAlg(fileInfo, 0, fileCapacity - 1);
}

void SortingCompetition::sortingAlg(char ** words, int left, int right) {
    if (left < right) {
        int j = partition(words, left, right);
        sortingAlg(words, left, j - 1);
        sortingAlg(words, j + 1, right);
    }
}

int SortingCompetition::partition(char** words, int p, int r) {
    int pivot = strlen(words[r]);

    while (p < r) {
        while (strlen(words[p]) < pivot)
            p++;
        while (strlen(words[r]) > pivot)
            r--;

        if (strlen(words[p]) == strlen(words[r]))
            p++;
        else if (p < r) {
            char* temp = words[p];
            words[p] = words[r];
            words[r] = temp;
        }

    }
    return r;
}

void SortingCompetition::outputData(const string& outputFileName) {
    ofstream output;
    output.open(outputFileName);
    for (int i = 0; i < fileCapacity; i++) {
        cout << fileInfo[i] << " ";
    }

    for (int i = 0; i < fileCapacity; i++) {
        //cout << copyInfo[i];
    }
    output.close();
}

SortingCompetition::~SortingCompetition() {
    delete[] fileInfo;
    delete[] copyInfo;
}
