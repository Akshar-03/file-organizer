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
            {".gif", "Images"},
            {".bmp", "Images"},
            {".webp", "Images"},
            {".svg", "Images"},
            {".heic", "Images"},
            {".ico", "Images"},

            {".pdf", "Documents"},
            {".txt", "Documents"},
            {".doc", "Documents"},
            {".docx", "Documents"},
            {".ppt", "Documents"},
            {".pptx", "Documents"},
            {".xls", "Documents"},
            {".xlsx", "Documents"},
            {".csv", "Documents"},

            {".mp3", "Music"},
            {".wav", "Music"},
            {".aac", "Music"},
            {".flac", "Music"},
            {".ogg", "Music"},
            {".m4a", "Music"},

            {".mp4", "Videos"},
            {".mkv", "Videos"},
            {".avi", "Videos"},
            {".mov", "Videos"},
            {".wmv", "Videos"},
            {".webm", "Videos"},

            {".zip", "Archives"},
            {".rar", "Archives"},
            {".7z", "Archives"},
            {".tar", "Archives"},
            {".gz", "Archives"},

            {".exe", "Programs"},
            {".msi", "Programs"},

            {".cpp", "Code"},
            {".c", "Code"},
            {".h", "Code"},
            {".hpp", "Code"},
            {".py", "Code"},
            {".java", "Code"},
            {".js", "Code"},
            {".html", "Code"},
            {".css", "Code"}};

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

string FileOrganizer::toLower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int moved = 0;
int skipped = 0;
int errors = 0;

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
            skipped++;
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
            errors++;
            cout << "Error while moving " << srcFile.filename() << " : " << e.what() << '\n';
        }
        moved++;
    }

    cout << "Organization Complete\n";
    cout << "Files moved   : " << moved << '\n';
    cout << "Files skipped : " << skipped << '\n';
    cout << "Errors        : " << errors << '\n';
}