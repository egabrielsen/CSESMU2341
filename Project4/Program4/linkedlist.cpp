#include "linkedlist.h"

LinkedList::LinkedList()
{
    head = cur = nullptr;
    visited = false;
}

LinkedList::LinkedList(string label) {
    this->label = label;
    head = cur = nullptr;
    visited = false;
}

bool LinkedList::getVisited() {
    return visited;
}

void LinkedList::setVisited(bool b) {
    visited = b;
}

void LinkedList::setLabel(string label) {
    this->label = label;
}

string LinkedList::getLabel() {
    return label;
}

Node* LinkedList::getHead() {
    return head;
}

void LinkedList::setCur(Node* p) {
    cur = p;
}

Node* LinkedList::getCur() {
    return cur;
}

void LinkedList::insert(string val, int cost) {
    cur = head;
    if (cur == nullptr) {
        Node* n = new Node(val, cost);
        head = n;
        cur = head;
    } else {
        while(cur->next != nullptr) {
            cur = cur->next;
        }
        Node* temp = new Node(val, cost);
        cur->next = temp;
        temp->next = nullptr;
    }
}

bool LinkedList::doesPathExist(string arrival, Node *cur) {
    if (cur->getLabel() == arrival) {
        return true;
    } else if (cur->getNext() == NULL) {
        return false;
    } else {
        doesPathExist(arrival, cur->next);
    }
    return true;
}

void LinkedList::printList() {
    Node *p = head;
    if (p == nullptr) {
    } else if (p->next != nullptr){
        while (p != nullptr) {
            cout << p->getLabel() << " | ";
            p = p->next;
        }
        cout << endl;
    } else {
        cout << p->getLabel() << endl;
    }
}

LinkedList::~LinkedList() {

}
