#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H

#include "index.h"
#include "hashmap.h"
#include <iostream>

using namespace std;
class HashTableIndex: public Index
{
private:
    HashMap<string> table;
public:
    HashTableIndex();
    void insert(const string &x);
    void print();
    bool contains(const string &x);
    ~HashTableIndex();
};

#endif // HASHTABLEINDEX_H
