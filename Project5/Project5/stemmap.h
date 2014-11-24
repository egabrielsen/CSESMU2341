#ifndef STEMMAP_H
#define STEMMAP_H
#include <string>
#include <unordered_map>

using namespace std;

class StemMap
{
private:
    unordered_map<string, string> hash1;
    unordered_map<string, string>:: const_iterator iterator;
public:
    StemMap();
    bool DoesWordExist(string &);
    void insert(string &, string &);
};

#endif // STEMMAP_H
