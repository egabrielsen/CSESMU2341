#ifndef AVLINDEX_H
#define AVLINDEX_H

#include "index.h"
#include "avltree.h"
#include <iostream>

using namespace std;
class AVLIndex: public Index
{
private:
    AvlTree<string> tree;
public:
    AVLIndex();
    void insert(const string &x);
    void print();
    bool contains(const string &x);
    ~AVLIndex();
};

#endif // AVLINDEX_H
