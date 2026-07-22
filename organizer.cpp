#include "organizer.h"
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

string FileOrganizer::getCategory(const string &extension)
{
    unordered_map<string, string> categories =
        {
            {".jpg", "Images"},
            {".jpeg", "Images"},
            {".png", "Images"},

            {".pdf", "Documents"},
            {".txt", "Documents"},

            {".mp3", "Music"},

            {".mp4", "Videos"},

            {".zip", "Archives"}};

    auto it = categories.find(extension);
    return (it != categories.end()) ? it->second : "Others";
}

fs::path FileOrganizer::getFileName(const fs::path &destinationFolder, const fs::path &sourceFile)
{
    fs::path destinationFile = destinationFolder / sourceFile.filename();

    int cnt = 1;

    while (fs::exists(destinationFile))
    {
        string newName = sourceFile.stem().string() + " (" + to_string(cnt) + ")" + sourceFile.extension().string();

        destinationFile = destinationFolder / newName;

        cnt++;
    }

    return destinationFile;
}

string toLower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void FileOrganizer::organize(const string &folderpath)
{
    fs::path folder(folderpath); // fs::path folder= folderpath;

    if (!fs::exists(folder)) // if path not exist, return.
    {
        cout << "Folder doesn't exist.\n";
        return;
    }

    for (const auto &entry : fs::directory_iterator(folder)) // for every entry(file) inside the folder
    {
        // skip if not regular file
        if (!entry.is_regular_file())
        {
            continue;
        }

        // source file path
        fs::path srcFile = entry.path();

        // get extension
        string extension = toLower(srcFile.extension().string());

        // find category
        string category = getCategory(extension);

        // create destination folder
        fs::path destinationFolder = folder / category;
        fs::create_directories(destinationFolder);

        // create destination file path
        fs::path destinationFile = getFileName(destinationFolder, srcFile);

        // move files to respective categories
        try
        {
            fs::rename(srcFile, destinationFile);

            cout << "moved: " << srcFile.filename() << " -> " << category << '\n';
        }
        catch (const fs::filesystem_error &e)
        {
            cout << "Error while moving " << srcFile.filename() << " : " << e.what() << '\n';
        }
    }
}