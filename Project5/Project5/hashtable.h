#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <vector>
#include <list>


using namespace std;

template <typename HashedObj>
class HashTable
{
private:
    vector<list<HashedObj> > theLists;
    int currentSize;
    void rehash();
    int myhash(const HashedObj &x);

public:
    explicit HashTable(int size = 101);
    bool contains(const HashedObj &x) const;
    void makeEmpty();
    void insert(const HashedObj &x);
    void print();
    void remove(const HashedObj &x);
    int hash(const string & key);
    int hash(int key);
    ~HashTable();
};


#endif // HASHTABLE_H
