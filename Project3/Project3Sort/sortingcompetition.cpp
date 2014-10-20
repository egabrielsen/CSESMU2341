#include "sortingcompetition.h"
#include <iostream>
#include <cstring>
#include <ostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include "string.h"

using namespace std;

// -- Constructor sets fileCapacity equal to 0
SortingCompetition::SortingCompetition() {
    fileCapacity = 0;
}

// -- Constructor with value sets the parameter equal to the file name
//    and the fileCapacity is equal to 0
SortingCompetition::SortingCompetition(const string& inputFileName) {
    fileName = inputFileName;
    fileCapacity = 0;
}

// -- Sets File name equal to the given input
void SortingCompetition::setFileName(const string& inputFileName) {
    fileName = inputFileName;
}

// -- Reads in the data given into an Array Data Structure
bool SortingCompetition::readData() {
    ifstream file(fileName);
    fileCapacity = 0;
    char temp[100];

    // clears all the info previously stored in temp[]
    for (int i = 0; i < 100; i++) {
        temp[i] = '\0';
    }

    // determine the size of the file (How many words are in the file)
    while (file >> temp) {
        fileCapacity++;
    }

    cout << "fileCapacity: " << fileCapacity << endl;

    file.close(); //close the file

    ifstream file1(fileName); // re-open file to store data inside the array

    // -- if there is nothing stored in the file, then the method returns false, else it will start storing data
    if (fileCapacity == 0) {
        file1.close();
        return false;
    } else {
        fileInfo = new char*[fileCapacity]; // initiate the data structure 'fileInfo'

        // -- empties whatever is currently stored in the data structure
        for (int i = 0; i < fileCapacity; i++) {
            fileInfo[i] = NULL;
        }


        char buffer[50]; // no word is longer than 50 letters
        long size = 0;  // variable used to increment the array

        // -- Store what is in the file into 'fileInfo'
        while (file1 >> buffer) {
            fileInfo[size] = new char[strlen(buffer) + 1];
            strcpy(fileInfo[size], buffer);
            size++; // go to next spot in the array
        }

        file1.close(); // close the file

        return true;
    }


}

// -- Copies the data in FileData over to CopyData in order to use for sorting
bool SortingCompetition::prepareData() {
    copyInfo = new char*[fileCapacity]; // initiate a new copyInfo array

    // -- copy info from 'FileInfo' to 'CopyInfo'
    for (int i = 0; i < fileCapacity; i++) {
        copyInfo[i] = new char[strlen(fileInfo[i]) + 1];
        strcpy(copyInfo[i], fileInfo[i]);
        *copyInfo[i] = toupper(*copyInfo[i]); // capitalize first letter of each word for sorting purposes
    }

    return true;
}

// -- Sorts the data by size and the alphabetically
void SortingCompetition::sortData() {
    if (fileCapacity < 2) {
        //do nothing to file. Its already sorted/nothing is in the file
    } else {
      // -- Sort file by Size
        sizeSortingAlg(copyInfo, 0, fileCapacity - 1);

       // -- Sort By alphabet per size
        int wordSize = strlen(copyInfo[fileCapacity - 1]); //holds the size of the word
        int size = fileCapacity - 1; // holds place in the file

        do {
            wordSize = strlen(copyInfo[size]); // wordSize = current size of the words
            int end = size; // the end holds the value of the last word of that size
            while (strlen(copyInfo[size]) == wordSize) { // loop through array until word is not of that size
                size --; // decrement the position of the array
                if (size == 0) {
                    break; // break when the end of the array has been reached
                }
            }
            int start = size + 1; // holds the value of the first word in that size
            alphabetize(copyInfo, start, end);  // aplhabetize the list of words at current size

        } while (size != 0); // run until reach the end of the array

    }

}

// -- adapted from: http://www.algolist.net/Algorithms/Sorting/Quicksort
// -- this recursively calls the alphebetize function to alphabetize set of words
void SortingCompetition::alphabetize(char ** words, long start, long end) {
    if (end - start < 2) { //Base case
        return;
    }

    long q = partitionA(words, start, end);  //partition the array of words
    alphabetize(words, start, q); // recursively call the alphabetize function for left side
    alphabetize(words, q, end); // recursively call the function for right side
}

// -- partitioning of alphabetizing algorithm
long SortingCompetition::partitionA(char** words, long p, long r) {
    char* x = words[p];
    char* y = words[(r - p) / 2 + p];
    char* z = words[r - 1];
    long i = p - 1;
    long j = r;

    // -- find the best place for the partition to begin
    if (((strcmp(y, x) > 0) && (strcmp(y, z) < 0)) || ((strcmp(y, z) > 0) && (strcmp(y, x) < 0))) {
        x = y;
    } else if (((strcmp(z, x) > 0) && (strcmp(z, y) < 0)) || ((strcmp(z, y) > 0) && (strcmp(z, x) < 0))) {
        x = z;
    }

    // runs until i > j
    while (1) {
        do {
            j--; // while the word in the array is higher in the alphabet than the partition x decrement j
        } while (strcmp(words[j], x) > 0);
        do {
            i++; // while the word in the array is lower in the alphabet than the partition x increment i
        } while (strcmp(words[i], x) < 0);
        if (i < j) {
            // swap words
            char* temp = words[i];
            words[i] = words[j];
            words[j] = temp;
        } else
            return j + 1; // returns current position of the array
    }
}

// -- sorts words by size
void SortingCompetition::sizeSortingAlg(char** words, long start, long end) {
    if (end - start < 2) {  //Base Case
        return;
    }

    long q = partition(words, start, end); //  partition the array of words
    sizeSortingAlg(words, start, q); // recursively call size function for left side
    sizeSortingAlg(words, q, end); // recursively call size function for right side
}

//  -- Partioning for the size Sorting Algorithm
long SortingCompetition::partition(char** words, long p, long r) {
    int x = strlen(words[p]);
    int y = strlen(words[(r - p) / 2 + p]);
    int z = strlen(words[r - 1]);
    long i = p - 1;
    long j = r;

    // find best place for partition
    if ((y > x && y < z) || (y > z && y < x)) {
        x = y;
    } else if ((z > x && z < y) || (z > y && z < x)) {
        x = z;
    }

    // runs until i > j
    while (1) {
        do {
            j--; // decrement j when the length of the word is more than the length of x
        } while (strlen(words[j]) > x);
        do {
            i++; // increment i when the length of the word is less than the length of x
        } while (strlen(words[i]) < x);
        if (i < j) {
            // swap the two words of different size
            char* temp = words[i];
            words[i] = words[j];
            words[j] = temp;
        } else
            return j + 1; // returns where the position of array is
    }

}

// -- displays the sorted info in the outputFile
void SortingCompetition::outputData(const string& outputFileName) {
    ofstream output;

    // clears whatever is in the file first
    output.open(outputFileName);
    output.clear();

    for (int i = 0; i < fileCapacity; i++) {
        output << copyInfo[i] << endl;
    }

    output.close();
}


// -- frees the values and deletes the pointers of 'fileInfo' and 'copyInfo'
SortingCompetition::~SortingCompetition() {
    for (int i = 0; i < fileCapacity; i++) {
        free(fileInfo[i]);
        free(copyInfo[i]);
    }

    delete[] fileInfo;
    delete[] copyInfo;
    fileCapacity = 0;

}
