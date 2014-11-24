#include "userinterface.h"

UserInterface::UserInterface()
{
    option = 0;
    testing = true;
}

void UserInterface::play(char * file) {
    while (testing) {
        cout << "Would you like to split the XML Files? (y/n)" << endl;
        string split;
        cin >> split;
        if (split == "y" || split == "Y") {
            pars.splitXML();
        }
        cout  << "How would you like to load your index?\n  1) AVL Tree\n  2) HashTable\n(1/2)\n" << endl;
        string choice;
        cin >> choice;
        if (choice == "1") {
            index = new AVLIndex();
        } else if (choice == "2") {
            index = new HashTableIndex();
        } else {
            cout << "invalid selection!!\nEnter either a 1 or 2" << endl;
        }

        pars.loadDocument(file);
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        pars.parseDocument2(index);
        end = std::chrono::system_clock::now();
        unsigned int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        std::cout << "\n\n Time: " << milliseconds << " milliseconds" << std::endl;

        cout << "File is Parsed: parser2 " << endl;
        cout << "Display Tree?" << endl;
        string response;
        cin >> response;
        if (response == "Y" || response == "y") {
            index->print();
            cout << endl << endl;
        }

        bool searching = true;
        while (searching) {
            cout << "Enter word to search: ";
            string word;
            cin >> word;
            if (index->contains(word)) {
                cout << "Found word!\n";
                cout << "Enter -1 to exit" << endl;
            } else if (word == "-1") {
                searching = false;
            } else {
                cout << "cound not find word";
                cout << "Enter -1 to exit" << endl;
            }
        }
        cout << "Test finished" << endl;
        testing = false;
    }

}
