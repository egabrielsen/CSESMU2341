#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "avltree.h"

using namespace std;

class Node
{
private:
    string word;
    AvlTree<DocFreq> freqTree;
    struct DocFreq{
        int docId;
        int frequency;
    };
public:
    Node();
    Node(int id);
    int getFrequency(int id);
};

#endif // NODE_H
