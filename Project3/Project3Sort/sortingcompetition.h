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
    void sizeSortingAlg(char**, long, long);
    void alphabetize(char**, long, long);
    long partition(char**, long, long);
    long partitionA(char**, long, long);
    void outputData(const string&);
    ~SortingCompetition();

};

#endif // SORTINGCOMPETITION_H
