#include "organizer.h"
#include <iostream>
#include <filesystem>
#include <unordered_map>

using namespace std;
namespace fs = std::filesystem;

void FileOrganizer::organize(const string &folderpath)
{
    fs::path folder(folderpath); // fs::path folder= folderpath;

    if (!fs::exists(folder)) // if path not exist, return.
    {
        cout << "Folder doesn't exist.\n";
        return;
    }

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
        string extension = srcFile.extension().string();

        // find category
        auto it = categories.find(extension);
        string category = (it != categories.end()) ? it->second : "Others";

        // create destination folder
        fs::path destinationFolder = folder / category;
        fs::create_directories(destinationFolder);

        // create destination file path
        fs::path destinationFile = destinationFolder / srcFile.filename();

        // handle duplicates
        int counter = 1;
        while (fs::exists(destinationFile))
        {
            string newName = srcFile.stem().string() + " (" + to_string(counter) + ")" + srcFile.extension().string();
            destinationFile = destinationFolder / newName;
            counter++;
        }

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