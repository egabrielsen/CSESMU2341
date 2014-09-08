// Erik Gabrielsen
// Project 1:  Laser Tag Game
// Date:  September 8, 2014

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

//-- initialize key functions/methods
void displayLowVerbosity(char** match, char** teamA, char** teamB, ostream &out);
void displayMediumVerbosity(char** match, char** teamA, char** teamB, char* sTeamA, char* sTeamB, ostream &out);
void displayHighVerbosity(char** match, char** teamA, char** teamB, ostream &out);
void getMatchInfo(char*, char** match);
void getTeamInfo(char*, char** team);
void winningInfo(char** tags, char** teamA, char** teamB, int size, int teamAscore, int teamBscore, ostream &out);
int assignScore(char** tags, int teamScore, int i);
int tagTotal(char** tags, char** team, int size);
int individualTags(char** tags, char** teamA, char** teamB, int size);

int main(int argc, char* argv[]) {
    // -- check the number of Arguments in Command Line
    if (argc != 6) {
        cout << "Invalid number of arguments in Command Line.\nUsage is: ./a.out <TeamA> <TeamB> <Match> <Output> <vlow | vmed | vhigh>" << endl;
    } else {
    // -- Run the main program
        int capacity = 10;
        int mCapacity = 30;
        char* sTeamA = argv[1]; // -- stores the Team 1 name of the file uploaded on Command Line
        char** cTeamA = new char*[capacity];;  // -- initialize char array that stores team info
        char* sTeamB = argv[2];  // -- stores the Team 1 name of the file uploaded on Command Line
        char** cTeamB = new char*[capacity];; // -- initializes char array that stores team info
        char* Smatch = argv[3];
        char** match = new char*[mCapacity];
        char* verbosity = argv[5];

        getTeamInfo(sTeamA, cTeamA); // -- call functions that stores info from text files
        getTeamInfo(sTeamB, cTeamB); // into arrays that will be used later for scoring
        getMatchInfo(Smatch, match);

        ofstream outputFile;  // -- open up the output file for storing the information
        outputFile.open ("output.txt");

        // -- display the info based on vlow, vmed, vhigh
        if (strcmp(verbosity, "vlow") == 0)
            displayLowVerbosity(match, cTeamA, cTeamB, outputFile);
        else if (strcmp(verbosity, "vmed") == 0) {
            displayMediumVerbosity(match, cTeamA, cTeamB, sTeamA, sTeamB, outputFile);
            displayLowVerbosity(match, cTeamA, cTeamB, outputFile);
        } else if (strcmp(verbosity, "vhigh") == 0) {
            displayHighVerbosity(match, cTeamA, cTeamB, outputFile);
            displayLowVerbosity(match, cTeamA, cTeamB, outputFile);
        } else
            cout << endl << "Invalid input:  Please enter number vlow, vmed, or vhigh\n" << endl;

        outputFile.close();  // -- close output file
        return 0;

        //-- end program
    }

}

void getTeamInfo(char* s, char** team) {
    // -- initializes a file from the ___.txt file in main for the team info
    ifstream in_file(s, ios::binary);

    // -- checks to see if file is open
    if (!in_file.is_open()) {
        cout << "File not opened..." << endl;
    }

    int size = 0; // -- size of the file
    char buffer[80]; // -- array of characters that temporary store values

    while (in_file >> buffer) { // -- assign the file data from in_file to buffer and then
        team[size] = new char[strlen(buffer) + 1]; // place data into char** team array
        strcpy(team[size], buffer);
        size++;
    }

    in_file.close();
}

void getMatchInfo(char* s, char** match) {
    // -- initializes a file from the ___.txt file in main for the match info
    ifstream in_file(s, ios::binary);

    // -- check to see if the file is open
    if (!in_file.is_open()) {
        cout << "File not opened..." << endl;
    }

    int size = 0;  // -- size of the file
    char buffer[80];  // -- array of characters that temp store values

    while (in_file >> buffer) {  // -- assign the file data from in_file to buffer and then
        match[size] = new char[strlen(buffer) + 1]; // place data into char** match array
        strcpy(match[size], buffer);
        size++;
    }

    in_file.close();
}

void displayLowVerbosity(char** match, char** teamA, char** teamB, ostream &out) {
    int teamAscore = 0;
    int teamBscore = 0;
    int mSize = 1;

    while (match[mSize] != NULL) { //establishes how many events occured
        mSize++;                    //(how many strings in the txt file)
    }

    char** tagInfo = new char*[(mSize - 1)];  //a new array that stores each string

    for (int i = 1; i < mSize; i++) { //this for loop stores the match info into tagInfo
        tagInfo[i-1] = match[i]; // -- sets the match info equal to the newTagInfo to use in winningInfo function

    }

    winningInfo(tagInfo, teamA, teamB, mSize, teamAscore, teamBscore, out); //function displays winning info
}

void displayMediumVerbosity(char** match, char** teamA, char** teamB, char* sTeamA, char* sTeamB, ostream &out) {

    out << endl << teamA[1] << endl; // -- display team1 name
    int size = 9;

    // -- for loop that goes through each player of teamA and finds number of tags
    // uses "tagTotal" function
    for (int i = 4; i < size; i += 2) {
        out << teamA[i] << " had a total of " << tagTotal(match, teamA, i) << " tags" << endl;
    }

    out << endl << endl << teamB[1] << endl; // -- display team2 name
    int sizeB = 9;

    // -- for loop that goes through each player of teamB and finds number of tags per player
    // uses "tagTotal" function
    for (int i = 4; i < sizeB; i += 2) {
        out << teamB[i] << " had a total of " << tagTotal(match, teamB, i) << " tags" << endl;
    }
}

void displayHighVerbosity(char** match, char** teamA, char** teamB, ostream &out) {
    int size = 0;
    int size2 = 0;

    while (teamA[size] != NULL)
        size++;
    while (teamB[size2] != NULL)
        size2++;

    cout << teamA[0] << " " << teamA[1] << endl;

    for (int i = 4; i < size; i = i + 2) {
        for (int j = 4; j < size2; j = j + 2) {
            cout << "   " << teamA[i] << " tagged " << teamB[j] << " " << individualTags(match, teamA, teamB, size) << " times" << endl;
        }
        cout << "   " << teamA[i] << " had a total of " << tagTotal(match, teamA, i) << " tags" << endl;
    }

    cout << teamB[0] << " " << teamB[1] << endl;

    for (int i = 4; i < size2; i = i + 2) {
        for (int j = 4; j < size; j = j + 2) {
            cout << "   " << teamB[i] << " tagged " << teamA[j] << " " << individualTags(match, teamA, teamB, size) << " times" << endl;
        }
        cout << "   " << teamB[i] << " had a total of " << tagTotal(match, teamB, i) << " tags" << endl;
    }

}

int individualTags(char** tags, char** teamA, char** teamB, int size) {
    int max = 0;
    int numberOfTags = 0;

    while (tags[max] != NULL)
        max++;


    for (int i = 1; i < max; i = i + 4) {
        //cout << tags[i] << endl << teamA[i] << endl << teamB[i] << endl;

        //if (strncmp(tags[i], teamA[i], 1) == 0 && strncmp(tags[i], teamB[i], 1) == 0 ) {
        //    numberOfTags++;
        //}
    }

    return numberOfTags;
}

int tagTotal(char** tags, char** team, int size) {
    int numberOfTags = 0;
    int capacity = 0;

    while (tags[capacity] != NULL) // -- establishes the size of the tagged info array
        capacity++;

    // -- for loop goes through tags array and compares it to the current team players number
    // in order to determine the number of tags
    for (int i = 1; i < capacity; i = i + 4) {
        if (strncmp(tags[i], team[size - 1], 1) == 0) { //string compare function
            numberOfTags++;
        }
    }

    return numberOfTags;
}

void winningInfo(char** tags, char** teamA1, char** teamB2, int size, int teamAscore, int teamBscore, ostream &out) {
    int capacity = 0;

    for (int t = 3; t <= size; t = t + 4) { // find size of array char** tags that supports who made the tags
        capacity++;
    }

    int tempSize = 0;  // the size of the temperary array storing info from tags[]
    char** temp = new char*[capacity];  // temp array for tags[]

    for (int t = 3; t <= size; t = t + 4) { //assign first value of each line to temp array
        temp[tempSize] = tags[t];
        tempSize++;
    }

    int temp2size = 0;
    int* tempTagger = new int[capacity];
    // -- for loop goes through each line to see who was the tagger to assign points
    // to the respective team
    for (int i = 0; i < size; i = i + 4) {
        // -- if statements to determine what team the tagger belongs to
        if (strncmp(tags[i], "1", 1) == 0) {
            tempTagger[temp2size] = 1;
            temp2size++;
            teamAscore = assignScore(tags, teamAscore, i); // call assignScore function
        } else if (strncmp(tags[i], "2", 1) == 0) {
            tempTagger[temp2size] = 1;
            temp2size++;
            teamAscore = assignScore(tags, teamAscore, i); // call assignScore function
        } else if (strncmp(tags[i], "3", 1) == 0) {
            tempTagger[temp2size] = 1;
            temp2size++;
            teamAscore = assignScore(tags, teamAscore, i); // call assignScore function
        } else if (strncmp(tags[i], "4", 1) == 0) {
            tempTagger[temp2size] = 2;
            temp2size++;
            teamBscore = assignScore(tags, teamBscore, i); // call assignScore function
        } else if (strncmp(tags[i], "5", 1) == 0) {
            tempTagger[temp2size] = 2;
            temp2size++;
            teamBscore = assignScore(tags, teamBscore, i); // call assignScore function
        } else if (strncmp(tags[i], "6", 1) == 0) {
            tempTagger[temp2size] = 2;
            temp2size++;
            teamBscore = assignScore(tags, teamBscore, i); // call assignScore function
        }

    }

    out << endl;
    // -- output for text file on winners and scores for each team
    out << teamA1[1] << ": " << teamAscore << " points" << endl;
    out << teamB2[1] << ": " << teamBscore << " points" << endl;

    if (teamAscore > teamBscore)
        out << "Overall Winners: " << teamA1[1] << endl;
    else if (teamBscore > teamAscore)
        out << "Overall Winners: " << teamB2[1] << endl;
    else
        out << "Its a Tie!!" << endl;



}

int assignScore(char** tags, int teamScore, int i) {
    // -- if statements to determine where the person tagged and..
    // assign correct amount of points to team
    if (strncmp(tags[i+3], "1", 1) == 0)
        return teamScore = teamScore + 5;
    else if (strncmp(tags[i+3], "2", 1) == 0)
        return teamScore = teamScore + 8;
    else if (strncmp(tags[i+3], "3", 1) == 0)
        return teamScore = teamScore + 10;
    else
        return teamScore = teamScore + 15;
}

/*int temp3size = 0;
int* tempTagged = new int[capacity];
for (int i = 1; i < size; i = i + 4) {
    if (strncmp(tags[i], "1", 1) == 0) {
        tempTagged[temp3size] = 1;
        temp3size++;
    } else if (strncmp(tags[i], "2", 1) == 0) {
        tempTagged[temp3size] = 1;
        temp3size++;
    } else if (strncmp(tags[i], "3", 1) == 0) {
        tempTagged[temp3size] = 1;
        temp3size++;
    } else if (strncmp(tags[i], "4", 1) == 0) {
        tempTagged[temp3size] = 2;
        temp3size++;
    } else if (strncmp(tags[i], "5", 1) == 0) {
        tempTagged[temp3size] = 2;
        temp3size++;
    } else if (strncmp(tags[i], "6", 1) == 0) {
        tempTagged[temp3size] = 2;
        temp3size++;
    }

}*/
