#include "stemmap.h"

StemMap::StemMap()
{

}

bool StemMap::DoesWordExist(string &unstemmed) {
    iterator = hash1.find(unstemmed);

    if (iterator != hash1.end()) {
        unstemmed = iterator->second;
        return true;
    }

    else
        return false;
}

void StemMap::insert(string &unstemmed, string &stemmed) {
    hash1.insert(make_pair(unstemmed, stemmed));
}


