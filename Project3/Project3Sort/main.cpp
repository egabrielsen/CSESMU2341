#include <iostream>
#include <cstring>
#include <chrono>
#include <ctime>
#include <fstream>
#include <ostream>
#include "string.h"
#include "sortingcompetition.h"
#include "sortingcompetition.cpp"

using namespace std;

bool checkCommandLine(int);

int main(int argc, char* argv[])  {
    if(checkCommandLine(argc)) {
        chrono::time_point<chrono::system_clock> start, end;

        SortingCompetition *game = new SortingCompetition(argv[1]);

        while (game->readData() && game->prepareData()) {
            start = chrono::system_clock::now();
            game->sortData();

            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            time_t end_time = chrono::system_clock::to_time_t(end);
            game->outputData(argv[2]);
            game->~SortingCompetition();

            cout << "finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s/n";
            break;
        }
    }
    return 0;
}

bool checkCommandLine(int arguments) {
    if (arguments != 3) {
        cout << "Invalid number of arguments in command line\n Need ./a.out <inputFile> <outputFile>" << endl;
        return false;
    } else {
        cout << "Welcome to my Sorting Algorithm: \n" << endl;
        return true;
    }
}

