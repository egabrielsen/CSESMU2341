#include <iostream>
#include <fstream>
#include <cstring>
#include <ostream>
#include <stack>

#include "linkedlist.h"
#include "linkedlist.cpp"

using namespace std;

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
        getline(f, depart, ',');
        getline(f, arrive, '\n');
        depart = removeSpace(depart);
        arrive = removeSpace(arrive);
        cout << "Flight " << i + 1 << ": " << depart << ", " << arrive << endl;
        int cost = 0;
        for (int i = 0; i < numF; i++) {
            if (depart == list[i]->getLabel()) {
                int leg = 1;
                int totalCost = 0;
                findPath(list[i]->getHead(), depart, arrive, out, leg, totalCost);
                cout << "Total Cost: $" << totalCost << endl;
                cost++;
            } else {
                // do nothing because there is no list at this point in the linked list
            }
        }
        if (cost == 0) {
            cout << "Flight not possible" << endl;
        }
        cout << endl;
    }
}

void findPath(Node* node, string depart, string arrival, ofstream &out, int& leg, int &totalCost) {
    bool found = false;
    while(!found) {
        if (node->getNext() == NULL && node->getTop() == NULL) {
            if (node->getLabel() == arrival) {
                totalCost += node->getCost();
                cout << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                found = true;
            }
            else {
                cout << "This flight is not available" << endl;
                found = true;
            }
        } else if (node->getNext() == NULL) {
            if (node->getLabel() == arrival) {
                totalCost += node->getCost();
                cout << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                found = true;
            } else {
                totalCost += node->getCost();
                cout << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                findPath(node->getTop(), node->getLabel(), arrival, out, leg, totalCost);
                found = true;
            }
        } else {
            while (node->getNext() != NULL) {
                if (node->getLabel() == arrival) {
                    totalCost += node->getCost();
                    cout << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                    return;
                } else {
                    if (node->getTop() == NULL) {
                        //totalCost += node->getCost();
                        cout << "Flight is not available" << endl;
                        found = true;
                        return;
                    } else {
                        Node *temp = new Node(node->getLabel(), node->getCost());
                        temp->setNext(node->getNext());
                        temp->setTop(node->getTop());
                        while(temp != NULL) {
                            if (temp->getLabel() == arrival) {
                                cout << "Leg "<< leg++ << ": " << depart << " to " << temp->getLabel() << " $" << temp->getCost() << endl;
                                found = true;
                                return;
                            } else {
                                temp = temp->getNext();
                            }
                        }
                        totalCost += node->getCost();
                        cout << "Leg "<< leg++ << ": " << depart << " to " << node->getLabel() << " $" << node->getCost() << endl;
                        findPath(node->getTop(), node->getLabel(), arrival, out, leg, totalCost);
                        return;
                    }
                }
            }
        }


    }


}

// --
bool departureExist(string a, string arrival, int cost, int i, LinkedList **& list) {
    for (int j = 0; j < i; j++) {
        if (list[j]->getLabel() == a) {
            list[j]->insert(arrival, cost);
            return true;
        }
    }
    return false;
}

string removeSpace(string input) {
    if (input[0] == ' ') {
        input.erase(0, 1);
    }
    return input;
}

bool commandLine(int a) {
    if (a != 4) {
        cout << "Invalid Prompt\n./a.out <FlightDataFile> <PathsToCalculateFile> <OutputFile> " << endl;
        return false;
    } else {
        return true;
    }
}
