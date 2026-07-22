#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

class FileOrganizer
{
public:
    void organize(const string &folderPath);

private:
    string getCategory(const string &extension);
    fs::path getFileName(const fs::path &destinationFolder, const fs::path &sourceFile);
    string toLower(string str);
};

#endif