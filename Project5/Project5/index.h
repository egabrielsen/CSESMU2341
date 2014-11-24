#ifndef INDEX_H
#define INDEX_H

//#include "avlindex.h"
//#include "hashtableindex.h"
#include <iostream>

using namespace std;


class Index
{
private:
    string word;
    int docID;
    int frequency;
    Index* root;

public:
    Index() {}
    virtual void insert(const string &x) = 0;
    virtual void print() = 0;
    virtual bool contains(const string &x) = 0;

    //virtual void insert(string word, int docID, int freq) = 0;
    //virtual IndexEntry search(string word) = 0;
    //virtual void writeToFile() = 0;
    //virtual void readFromFile() = 0;
};

#endif // INDEX_H
