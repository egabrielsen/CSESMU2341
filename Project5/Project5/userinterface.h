#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "parser.h"
#include "parser.cpp"
#include "index.h"
#include "avlindex.h"
#include "avlindex.cpp"
#include "hashtableindex.h"
#include "hashtableindex.cpp"
#include <chrono>
#include <iostream>

using namespace std;

class UserInterface
{
private:
    bool testing;
    int option;
    Index *index;
    Parser pars;
public:
    UserInterface();
    void play(char* file);
};

#endif // USERINTERFACE_H
