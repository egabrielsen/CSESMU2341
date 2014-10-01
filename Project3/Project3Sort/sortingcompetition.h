#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <iostream>

using namespace std;

class SortingCompetition    {
private:
    string fileName;
    long fileCapacity;
    char** fileInfo;
    char** copyInfo;
public:
    SortingCompetition();
    SortingCompetition(const string& inputFileName);
    void setFileName(const string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void sortingAlg(char**, int, int);
    int partition(char**, int, int);
    void outputData(const string&);
    ~SortingCompetition();

};

#endif // SORTINGCOMPETITION_H
