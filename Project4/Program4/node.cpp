#include <cstring>
#include <iostream>
#include "node.h"

using namespace std;

Node::Node()
{
    visited = false;
}

Node::Node(string label, int cost) {
    this->label = label;
    this->cost = cost;
    visited = false;
    top = nullptr;
}

void Node::setTop(Node *t) {
    top = t;
}

Node* Node::getTop() {
    return top;
}

void Node::setVisited(bool b) {
    visited = b;
}

bool Node::getVisited() {
    return visited;
}

void Node::setNext(Node *n) {
    this->next = n;
}

Node* Node::getNext() {
    return next;
}

void Node::setLabel(string l) {
    this->label = l;
}

string Node::getLabel() {
    return label;
}

void Node::setCost(int cost) {
    this->cost = cost;
}

int Node::getCost() {
    return cost;
}

Node::~Node() {

}

