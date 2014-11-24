#include "avlindex.h"

AVLIndex::AVLIndex()
{
    cout << "creating new AVL Index..." << endl;
}

void AVLIndex::insert(const string &x) {
    tree.insert(x);
}

void AVLIndex::print() {
    tree.print();
}

bool AVLIndex::contains(const string &x) {
    return tree.contains(x);
}

AVLIndex::~AVLIndex() {
    tree.makeEmpty();
    tree.~AvlTree();
}
