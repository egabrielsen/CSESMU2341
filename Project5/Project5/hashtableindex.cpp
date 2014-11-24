#include "hashtableindex.h"

HashTableIndex::HashTableIndex()
{
    cout << "creating HashTable Index..." << endl;
}

void HashTableIndex::insert(const string &x) {
    table.insert(x);
}

void HashTableIndex::print() {
    table.print();
}

bool HashTableIndex::contains(const string &x) {
    return table.contains(x);
}

HashTableIndex::~HashTableIndex() {

}
