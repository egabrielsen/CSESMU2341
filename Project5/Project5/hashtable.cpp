#include "hashtable.h"


void HashTable::insert(const string &x) {
    list<HashedObj> & whichList = theLists[myhash(x)];
    if (find(whichList.begin(), whichList.end(), x) != whichList.end()) {
        //increase the frequency of the word
    }
    whichList.push_back(x);

    if (++currentSize > theLists.size())
        rehash();
}

int HashTable::myhash(const HashedObj &x) {
    int hashVal = hash(x);

    hashVal %= theLists.size();
    if (hashVal < 0)
        hashVal += theLists.size();

    return hashVal;
}

size_t HashTable::hash(const string &key) {

}

void HashTable::makeEmpty() {
    for (int i = 0; i < theLists.size(); i++) {
        theLists[i].clear();
    }
}

bool HashTable::contains(const HashedObj &x) const {
    const list<HashedObj> & whichList = theLists[myhash(x)];
    return find(whichList.begin(), whichList.end(), x) != whichList.end();
}

bool remove(const HashedObj &x) const {
    list<HashedObj> &whichList = theLists[myhash(x)];
    list<HashedObj>::iterator itr = find(whichList.begin(), whichList.end(), x);

    if (itr == whichList.end())
        return false;

    whichList.erase(itr);
    --currentSize;
    return true;
}

void HashTable::rehash() {
    vector<list<HashedObj> > oldLists = theLists;
    // create new double-sized, empty table
    theLists.resize(nextPrime(2 * theLists.size()));
    for (int i = 0; i < theLists.size(); i++)
        theLists[i].clear();

    //copy table over
    currentSize = 0;
    for (int i = 0; i < oldLists.size(); i++) {
        list<HashedObj>::iterator itr = oldLists[i].begin();
        while(itr != oldLists[i].end())
            insert(*itr++);
    }
}

HashTable::~HashTable() {
    makeEmpty();
}
