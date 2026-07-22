#include<iostream>
#include "organizer.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        cout << "Usage: " << argv[0] << " <folder_path>\n";
        return 1;
    }
    string folderPath = argv[1];

    FileOrganizer organizer;
    organizer.organize(folderPath);

    return 0;
}