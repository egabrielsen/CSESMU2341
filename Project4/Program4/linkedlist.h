#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include "node.cpp"

class LinkedList
{
private:
    Node* head;
    Node* cur;
    string label;
    bool visited;
public:
    LinkedList();
    LinkedList(string label);
    bool getVisited();
    void setVisited(bool b);
    Node* getCur();
    void setCur(Node* p);
    void setLabel(string label);
    string getLabel();
    Node* getHead();
    void insert(string val, int cost);
    bool doesPathExist(string arrival, Node* cur);
    void printList();
    ~LinkedList();
};

#endif // LINKEDLIST_H
