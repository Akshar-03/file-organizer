#include<iostream>
#include "organizer.h"
using namespace std;

int main()
{
    string folderpath;
    cout << "Enter folder path: ";
    getline(cin, folderpath);

    FileOrganizer organizer;

    organizer.organize(folderpath);

    return 0;
}