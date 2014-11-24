#include "userinterface.h"
#include "userinterface.cpp"

#include <chrono>
#include <iostream>

using namespace std;
using namespace pugi;

int main(int argc, char* argv[]) {

    UserInterface face;
    face.play(argv[1]);

    return 0;
}

