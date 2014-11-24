#ifndef HASHMAP_H
#define HASHMAP_H
#include <string>
#include <unordered_map>

using namespace std;

template <typename Comparable>
class HashMap
{
private:
    unordered_map<Comparable, Comparable> hash;
    typename unordered_map<Comparable, Comparable>::const_iterator it;
public:
    HashMap() {}
    bool contains(const Comparable &x) {
        it = hash.find(x);

        if (it == hash.end()) {
            return false;
        }
        else
            return true;
    }

    void insert(const Comparable &x) {
        hash.insert(make_pair(x, x));
    }

    void print() {
        for (auto it = hash.begin(); it != hash.end(); ++it) {
            cout << it->first << " : " << it->second << endl;
        }
    }
};

#endif // HASHMAP_H
