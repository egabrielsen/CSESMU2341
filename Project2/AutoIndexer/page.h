#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <fstream>
#include <cstring>

class Page {

private:
    int capacity; //max capacity of information provided.
    char** pages; //array that stores page numbers
    int pageIndex; //index of pages array

public:
    Page();
    ~Page();
    void getFileSize(char*);
    char** getPage();
    int getCapacity();
    void getInfo(char*, char**);

};

#endif // PAGE_H
