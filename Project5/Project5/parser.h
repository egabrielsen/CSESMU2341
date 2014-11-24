#ifndef PARSER_H
#define PARSER_H
#include "pugixml.hpp"
#include "pugixml.cpp"
#include "index.h"
#include "index.cpp"
#include "avltree.h"
#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <functional>
#include <dirent.h>
#include <sstream>
#include "porter2_stemmer.cpp"
#include "porter2_stemmer.h"
#include "stemmap.h"
#include "stemmap.cpp"

using namespace std;

class Parser
{
private:
    pugi::xml_document doc;
    AvlTree<string> stopWords;
    vector<int> idNumbers;
    StemMap stem;

public:
    Parser();
    ~Parser();
    void loadDocument(char* arg);
    void splitXML();
    void parseDocument(Index *&tree);
    void parseDocument2(Index *&tree);
    void createSWTree();
    bool isStop(string s);
    string stringBreaker(string s);
    void strip(string &s);
    void outputAddress(const pugi::xml_node& address);
};

#endif // PARSER_H
