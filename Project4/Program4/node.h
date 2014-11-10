#ifndef NODE_H
#define NODE_H

#include <cstring>
#include <iostream>

using namespace std;

class Node
{
friend class LinkedList;
private:
    Node* next;
    Node* top;
    int cost;
    string label;
    bool visited;
public:
    Node();
    Node(string label, int cost);
    void setTop(Node* t);
    Node* getTop();
    void setVisited(bool b);
    bool getVisited();
    void setNext(Node* n);
    Node* getNext();
    void setLabel(string l);
    string getLabel();
    void setCost(int cost);
    int getCost();
    ~Node();
};


#endif // NODE_H
