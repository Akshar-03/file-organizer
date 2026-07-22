#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <string>

class FileOrganizer
{
public:
    void organize(const std::string &folderPath);

private:
    string getCategory(const std::string &extension);
    fs::path getFileName(const fs::path &destinationFolder, const fs::path &sourceFile);
    string toLower(string str);
};

#endif