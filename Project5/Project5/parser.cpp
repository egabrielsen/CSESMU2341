#include "parser.h"




Parser::Parser()
{

}

void Parser::loadDocument(char *arg) {
    pugi::xml_parse_result result = doc.load_file(arg);
    //cout << "Load result: " << result.description() << endl;

}

void Parser::splitXML() {
    //int num = 0;
    for (pugi::xml_node node = doc.child("mediawiki").first_child(); node; node = node.next_sibling()) {
        pugi::xml_document newDocument;

        pugi::xml_node tnode = newDocument.append_child("id");
        const char* id = node.child("id").child_value();
        string id1 = node.child("id").child_value();
        tnode.append_child(pugi::node_pcdata).set_value(id);

        //-- use pushback here to load id into vector
        idNumbers.push_back(atoi(id1.c_str()));

        pugi::xml_node t2node = newDocument.append_child("title");
        const char* title = node.child("title").child_value();
        t2node.append_child(pugi::node_pcdata).set_value(title);

        pugi::xml_node t3node = newDocument.append_child("text");
        t3node.append_child(pugi::node_pcdata).set_value(node.child("revision").child("text").child_value());

        ofstream out("WikiDump/" + id1 + ".xml");
        newDocument.save(out, " ", pugi::format_default);
        out.close();

    }
    cout << "File is split" << int(idNumbers.size()) << endl;
}

void Parser::parseDocument(Index *&tree) {

    createSWTree();
    //pugi::xml_node node = doc.child("mediawiki").first_child();
    DIR *dir;
    struct dirent *ent;
    int times = 10;
    int loading = 0;
    if ((dir = opendir("WikiDump/")) != NULL)  {
        cout << "Loading files...\n" << endl;
        while((ent = readdir(dir)) != NULL ) {
            //cout << "*";
            string fileName = ent->d_name;
            //ifstream file("WikiDump/" + fileName);
            string fileName2 = "WikiDump/" + fileName;
            char* fileName3 = new char[fileName2.length() + 1];
            strcpy(fileName3, fileName2.c_str());
            loadDocument(fileName3);
            loading ++;
            typedef vector<string> WordVec;

            // -- passing in title
            WordVec words;
            string title = doc.child("title").child_value();
            string tempTitle = stringBreaker(title);
            stringstream Parse(tempTitle);
            string word;
            while (Parse >> word) {
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                //StemEnglish(word);
                if (stopWords.contains(word)) {
                    // dont store;
                } else {
                    words.push_back(word);
                }
            }
            for (WordVec::iterator it = words.begin(); it != words.end(); ++it) {
                if(stopWords.contains(*it)) {
                    words.erase(it);
                } else {
                    tree->insert(*it);
                    //cout << (*it) << endl;
                }
            }

            // -- passing in text
            WordVec words2;
            string text = doc.child("text").child_value();
            string tempText = stringBreaker(text);
            stringstream Parse2(tempText);
            string word2;

            while (Parse2 >> word2) {
                transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
                //StemEnglish(word);
                if (stopWords.contains(word2)) {
                    // dont store;
                } else {
                    words2.push_back(word2);
                }
            }
            for (WordVec::iterator it = words2.begin(); it != words2.end(); ++it) {
                if(stopWords.contains(*it)) {
                    words2.erase(it);
                } else {
                    tree->insert(*it);
                    //cout << (*it) << endl;
                }
            }

            //cout << title << endl;
            delete[] fileName3;
            words.empty();
            //words2.erase();
            words.erase(words.begin(), words.end());
            words2.erase(words2.begin(), words2.begin());

            times--;
        }
        closedir(dir);
    } else {
        perror("");
        cout << EXIT_FAILURE;
    }


    //pugi::xml_node node = doc.child("mediawiki").first_child(); node; node = node.next_sibling()
    cout << "\n\nIndex created: parser1\n" << endl;
    cout << "Display Tree?" << endl;
    string response;
    cin >> response;
    if (response == "Y" || response == "y") {
        tree->print();
    }


}

void Parser::parseDocument2(Index *&tree) {
    bool containsNonAlpha;
    bool continueParsing;
    createSWTree();
    pugi::xml_node node = doc.child("mediawiki").first_child();


    for (int i = 0; i < 80000; i++) {
        //pugi::xml_node node = doc.child("mediawiki").first_child(); node; node = node.next_sibling()


        // -- passing in title
        int idNum = atoi(node.child("id").child_value());
        //cout << idNum << endl;

        string tempTitle = stringBreaker(node.child("title").child_value());
        stringstream Parse(tempTitle);
        string word;
        continueParsing = true;
        while (Parse >> word && continueParsing) {
            containsNonAlpha = find_if(word.begin(), word.end(), not1(ptr_fun((int(*)(int))isalpha))) != word.end();
            if (containsNonAlpha) {
                // do nothing with the word
                continueParsing = false;
            } else {
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                if (!stem.DoesWordExist(word)) {
                    string tempWord = word;
                    Porter2Stemmer::stem(word);
                    stem.insert(tempWord, word);
                }
                if (stopWords.contains(word)) {
                    // dont store;
                } else {
                    tree->insert(word);
                }
                continueParsing = true;
            }
        }
        if (continueParsing) {

            // -- passing in text
            string tempText = stringBreaker(node.child("revision").child("text").child_value());
            stringstream Parse2(tempText);
            string word2;

            while (Parse2 >> word2) {
                containsNonAlpha = find_if(word2.begin(), word2.end(), not1(ptr_fun((int(*)(int))isalpha))) != word2.end();
                if (containsNonAlpha) {
                    //do nothing with word
                } else {
                    transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
                    if (!stem.DoesWordExist(word2)) {
                        string tempWord2 = word2;
                        Porter2Stemmer::stem(word2);
                        stem.insert(tempWord2, word2);
                    }
                    if (stopWords.contains(word2)) {
                        // dont store;
                    } else {
                        tree->insert(word2);
                    }
                }
            }
        }

        node = node.next_sibling();

    }


}




void Parser::outputAddress(const pugi::xml_node &address) {
    cout << address.child_value("id") << endl;
    cout << address.child_value("title") << endl;
}

// -- stores stop words in AVLTree
void Parser::createSWTree() {
    ifstream file("stopWords.txt");
    int size = 661;
    string word;
    for(int i = 0; i < size; i++) {
        getline(file, word);
        stopWords.insert(word);
    }


    // -- displays the whole tree
    //stopWords.print();
}

//makes the word lower case and then compares with stop word
bool Parser::isStop(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (stopWords.contains(s))
        return true;
    else
        return false;
}

// -- replaces symbols with a space for reading purposes
string Parser::stringBreaker(string s) {
    size_t found;

    found = s.find_first_of("|\?/!#%$&*-();:.,+=_-@^[]{}<>\"");
    while (found != string::npos) {
        s[found] = ' ';
        found = s.find_first_of("|\?/!#%$&*-();:.,+=_-@^[]{}<>\"", found + 1);
    }

    return s;
}

void Parser::strip(string &s) {
    string::iterator i = s.begin();
    while (ispunct(*i))
        s.erase(i);
    string::reverse_iterator j = s.rbegin();
    while (ispunct(*j)) {
        s.resize(s.length() - 1);
        j = s.rbegin();
    }
}

Parser::~Parser() {

}
