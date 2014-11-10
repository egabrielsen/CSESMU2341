#include <iostream>
#include <fstream>
#include <cstring>
#include <ostream>
#include <stack>

#include "linkedlist.h"
#include "linkedlist.cpp"

using namespace std;

//-- declare methods/functions
bool commandLine(int);
string removeSpace(string input);
void readFile(char* file, LinkedList**& list, ofstream& out, int &num);
void assignTopPointers(LinkedList**& list, int num);
void setPaths(char* file, LinkedList**& list, ofstream& out, int num);
bool departureExist(string a, string arrival, int cost, int i, LinkedList **&list);
void findPath(Node* list, string depart, string arrival, ofstream& out, int& indexMax, int& totalCost);

int main(int argc, char* argv[]) {
    if (commandLine(argc)) {
        ofstream output;
        output.open(argv[3]); // open output file to begin writing out to file
        int numOfFlights;
        LinkedList** list;  // define a linked list of linked lists

        // -- read the file and create the data structure of linked lists
        readFile(argv[1], list, output, numOfFlights);

        // -- assign Top pointers which point to the other part in the data structure (making it an adjacency list)
        assignTopPointers(list, numOfFlights);

        // -- reading in path file and finding the paths
        setPaths(argv[2], list, output, numOfFlights);

        // - close the output file
        output.close();
    }
    return 0;
}

void readFile(char *file, LinkedList **&list, ofstream& out, int &num) {
    ifstream f(file);

    //-- used for reading in file
    string line;
    string departure;
    string arrival;
    string value;

    // -- get the first line of file, create a data structure containing the appropriate size
    getline(f, line);
    num = atoi(line.c_str());
    list = new LinkedList*[num];

    // -- read in the rest of the file

    for (int i = 0; i < num; i++) {
        getline(f, departure, ','); // read line until comma
        getline(f, arrival, ',');
        arrival = removeSpace(arrival); //remove the space before the word
        getline(f, value, '\n');
        value = removeSpace(value); // remove space before the word
        int num1 = atoi(value.c_str()); //convert string to int
        if (departureExist(departure, arrival, num1, i, list)) {
            // if the departure already exists
            // create an empty list at this spot
            // then insert node with data at spot where departure already exists
            list[i] = new LinkedList(" ");
        } else {
            // create a new Linkedlist at list[i]
            list[i] = new LinkedList(departure);
            // -- insert the first node into the Linked List
            list[i]->insert(arrival, num1);
        }

    }
}


// -- this function assigns the top pointers so that if a node is equivalent to another departure linked list,
//    it will then point to the head node of that linked list
void assignTopPointers(LinkedList **&list, int num) {
    // -- outer for loop loops through all the linked lists in the list pointer
    for (int i = 0; i < num; i++) {
        // -- if the linked list isnt empty continue here
        if (list[i]->getLabel() != " ") {
            // -- compares the current node to head node of list to see if there is only one node in the list
            if (list[i]->getCur() == list[i]->getHead()) {
                // -- for loop compares the node label to each list label in the data structure
                for (int j = 0; j < num; j++) {
                    if (list[i]->getHead()->getLabel() == list[j]->getLabel()) {
                        // -- if both the labels match, then it assigns a top pointer to the node in the list and points it to the head of that list
                        list[i]->getHead()->setTop(list[j]->getHead()); // points the top pointer of head node to its flight options
                    }
                }
            } else { // -- when there is more than one node in the list
                list[i]->setCur(list[i]->getHead()); // sets cur = head
                while (list[i]->getCur() != nullptr) { // iterates through the list until reaches the end of the list
                    // -- for loop compares each node label to a list label in data structure
                    for (int k = 0; k < num; k++) {
                        if (list[i]->getCur()->getLabel() == list[k]->getLabel()) {
                            // if the labels match then set the top pointer to the head of that list
                            list[i]->getCur()->setTop(list[k]->getHead());
                        }
                    }
                    // set the current node to the next node to iterate through the list
                    list[i]->setCur(list[i]->getCur()->getNext());
                }
            }
        } else {
            // do nothing if there is no list at list[i]
        }
    }
}

void setPaths(char *file, LinkedList**& list, ofstream& out, int numF) {
    ifstream f(file);
    string num;
    string depart;
    string arrive;

    getline(f, num);
    int numOfPaths = atoi(num.c_str());

    // -- read in the rest of the file

    for (int i = 0; i < numOfPaths; i++) {
        // -- get information from the line and place into string variables
        getline(f, depart, ',');
        getline(f, arrive, '\n');
        depart = removeSpace(depart);
        arrive = removeSpace(arrive);

        // display the desired flight
        out << "Flight " << i + 1 << ": " << depart << ", " << arrive << endl;

        int cost = 0; // cost will keep track if there is a flight taking place or not
        for (int i = 0; i < numF; i++) {
            if (depart == list[i]->getLabel()) {
                int leg = 1;
                int totalCost = 0; // set total cost to 0 everytime at beginning
                findPath(list[i]->getHead(), depart, arrive, out, leg, totalCost); // finds the path to destination
                out << "Total Cost: $" << totalCost << endl; // displays the cost
                cost++; //incriment cost by one to show that a flight plan exists
            } else {
                // do nothing because there is no list at this point in the linked list
            }
        }
        if (cost == 0) {
            // -- if cost is 0 that means there is no flight possible
            out << "Flight not possible" << endl;
        }
        out << endl;
    }
}

void findPath(Node* node, string depart, string arrival, ofstream &out, int& leg, int &totalCost) {
    bool found = false;

    // -- while loop runs until the node is found or if it does not exist
    while(!found) {
        // -- if the node is the last node in the list with nowhere else to go
            //this serves as "base case"
        if (node->getNext() == NULL && node->getTop() == NULL) {
            // -- node either matches destination else it does not and the flight is not available
            if (node->getLabel() == arrival) {
                totalCost += node->getCost();
                // display the leg of the flight
                out << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                found = true; // terminates while loop
            }
            else {
                out << "This flight is not available" << endl;
                found = true; // terminates while loop
            }

        // -- else if the node has a top pointer but is at the end of the current list...
        } else if (node->getNext() == NULL) {
            // if the node is the right node, return that as the leg, recursive use findPath with the top pointer
            if (node->getLabel() == arrival) {
                totalCost += node->getCost(); // increment the cost for total
                out << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                found = true; // terminate loop
            } else {
                totalCost += node->getCost();
                out << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                findPath(node->getTop(), node->getLabel(), arrival, out, leg, totalCost); // find path with the top pointer node
                found = true; // terminate loop
            }
        } else {
            // -- go through the list and find a node that either is the right node or has a top pointer, if it has top, take the top and
            // search through that list.
            while (node->getNext() != NULL) {
                if (node->getLabel() == arrival) {
                    totalCost += node->getCost();
                    out << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                    return;
                } else {
                    if (node->getTop() == NULL) {
                        //flight isnt available if nothing in the list matches and none of them have a top pointer
                        out << "Flight is not available" << endl;
                        found = true; // terminate loop
                        return;
                    } else {
                        // -- set up a temperary node to search through list while keeping current position node
                        Node *temp = new Node(node->getLabel(), node->getCost());
                        temp->setNext(node->getNext());
                        temp->setTop(node->getTop());
                        // go through the list and compare if equal to arrival
                        while(temp != NULL) {
                            if (temp->getLabel() == arrival) {
                                out << "Leg "<< leg++ << ": " << depart << " to " << temp->getLabel() << " $" << temp->getCost() << endl;
                                found = true; // terminate loop
                                return;
                            } else {
                                temp = temp->getNext(); // go to the next node
                            }
                        }
                        totalCost += node->getCost();
                        out << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                        // if the node is still not found, branch to the top and recursively do the same thing with that list
                        findPath(node->getTop(), node->getLabel(), arrival, out, leg, totalCost);
                        return;
                    }
                }
            }
        }


    }


}

// -- discovers if the departure already exists and returns true if it does
// function also inserts a node to the current linked list at that particular spot if the departure list already exists.
bool departureExist(string a, string arrival, int cost, int i, LinkedList **& list) {
    for (int j = 0; j < i; j++) {
        if (list[j]->getLabel() == a) {
            list[j]->insert(arrival, cost);
            return true;
        }
    }
    return false;
}

// -- removes the extra space at the beginning of the getline
string removeSpace(string input) {
    if (input[0] == ' ') {
        input.erase(0, 1);
    }
    return input;
}

// -- checks to see if the right number of command line statements
bool commandLine(int a) {
    if (a != 4) {
        cout << "Invalid Prompt\n./a.out <FlightDataFile> <PathsToCalculateFile> <OutputFile> " << endl;
        return false;
    } else {
        return true;
    }
}
