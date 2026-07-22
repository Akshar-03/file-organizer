# File Organizer

A command-line C++ application that automatically organizes files into categorized folders based on their file extensions.

## Features

- Organizes files into category folders
- Supports images, documents, music, videos, archives, programs and source code files
- Prevents overwriting files by automatically generating unique filenames
- Case-insensitive extension matching
- Displays an operation summary
- Accepts folder paths through command-line arguments

## Supported Categories

| Category | Examples |
|----------|----------|
| Images | .jpg, .png, .gif, .bmp, .webp |
| Documents | .pdf, .docx, .txt, .xlsx |
| Music | .mp3, .wav, .flac |
| Videos | .mp4, .mkv, .avi |
| Archives | .zip, .rar, .7z |
| Programs | .exe, .msi |
| Code | .cpp, .h, .py, .java |

## Technologies

- C++17
- Standard Template Library (STL)
- std::filesystem
- Git

## Project Structure


file-organizer/
├── README.md
├── .gitignore
├── main.cpp
├── organizer.cpp
└── organizer.h

## Requirements

- C++17 compatible compiler
- Windows, Linux or macOS

## Build

Compile using:

```bash
g++ main.cpp organizer.cpp -o main
```

## Usage

Run the program:

```bash
./main "path/to/folder"
```

Windows example:

```bash
main "C:\Users\YourName\Downloads"
```

## Example

```
Moved: image.jpg -> Images
Moved: song.mp3 -> Music
Moved: notes.pdf -> Documents

Organization Complete
Files moved   : 3
Files skipped : 0
Errors        : 0
```