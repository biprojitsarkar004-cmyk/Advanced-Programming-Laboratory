#  0714 02 CSE 2100

Documentation: Code Quality Improvements

# File Search Utility — v2

A lightweight Windows desktop application written in **C language** that allows users to search for files and folders by name through a clean graphical user interface (GUI). Built entirely using the Windows API (WinAPI) without any external libraries.

---

## Table of Contents

- [Features](#features)
- [Screenshots](#screenshots)
- [Requirements](#requirements)
- [Installation](#installation)
- [Build](#build)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [How It Works](#how-it-works)
- [Tech Stack](#tech-stack)
- [Known Limitations](#known-limitations)
- [Future Improvements](#future-improvements)
- [License](#license)

---

## Features

- Search files **and** folders by name simultaneously
- **Case-insensitive** search — no need to worry about uppercase or lowercase
- **Recursive search** — automatically scans all sub-folders inside the selected directory
- Displays search results in a structured table with **Type**, **Path**, and **Size** columns
- Shows file size in a human-readable format (B / KB / MB)
- **Browse button** for easy folder selection using the system folder picker dialog
- **Clear button** to reset results and start a new search
- Minimal and responsive GUI with a custom header bar
- Built as a standalone `.exe` — no installation required

---

## Requirements

- **Operating System:** Windows 7 or later
- **Compiler:** GCC via MinGW — download from [winlibs.com](https://winlibs.com)

---

## Installation

### Step 1 — Download MinGW

Go to [winlibs.com](https://winlibs.com) and download the latest **GCC + MinGW-w64** release (Win64, ZIP format).

### Step 2 — Extract MinGW

Extract the ZIP file and place the folder at:
```
C:\mingw64
```

### Step 3 — Add MinGW to PATH

1. Open Start Menu and search for **"Environment Variables"**
2. Click **"Edit the system environment variables"**
3. Under **System Variables**, find **Path** and click **Edit**
4. Click **New** and add:
   ```
   C:\mingw64\bin
   ```
5. Click **OK** on all dialogs

### Step 4 — Verify Installation

Open a terminal (PowerShell or CMD) and run:
```
gcc --version
```
If a version number appears, the installation was successful.

---

## Build

Open a terminal inside the project folder and run the build script:

```
.\build.bat
```

The script will:
1. Check if GCC is available
2. Create the `bin\` and `build\` directories if they do not exist
3. Compile all source files
4. Output the executable to `bin\FileSearch.exe`

---

## Usage

Run the application:
```
bin\FileSearch.exe
```
Or double-click `FileSearch.exe` inside the `bin\` folder.

### Step-by-Step Guide

1. Click the **Browse** button to open the folder picker and select the root directory where you want to search
2. Type the file or folder name (or part of it) in the **"File / Folder Name"** input box
   - Example: typing `mydocs` will match `mydocs.txt`, `mydocs_backup`, `my_mydocs_folder`, etc.
3. Click **Search**
4. All matching files and folders will appear in the result table below
5. Click **Clear** to reset the results and perform a new search

### Result Table

| Column | Description |
|--------|-------------|
| Type   | Indicates whether the result is a `FILE` or `FOLDER` |
| Path   | The full absolute path of the file or folder |
| Size   | File size displayed as B, KB, or MB (folders show `—`) |

---

## Project Structure

```
file-search-utility/
├── src/
│   ├── main.c        → Program entry point — initializes the window and runs the message loop
│   ├── gui.c         → All GUI logic — window creation, controls, layout, and event handling
│   ├── search.c      → Core search engine — traverses directories and finds matches
│   └── utils.c       → Utility functions — string helpers and file size formatter
│
├── include/
│   ├── gui.h         → Declarations for GUI functions and control IDs
│   ├── search.h      → Declarations for search functions and result data structures
│   └── utils.h       → Declarations for utility/helper functions
│
├── bin/              → Output directory — contains FileSearch.exe after build
├── build/            → Intermediate directory — contains compiled object files
├── build.bat         → Windows batch script to compile the project
├── .gitignore        → Tells Git to ignore bin/, build/, and compiled files
└── README.md         → Project documentation
```

---

## Architecture

The project follows a **modular architecture** where each concern is separated into its own file:

```
main.c
  └── Initializes GUI framework
  └── Creates the main window
  └── Runs the Windows message loop

gui.c
  └── Handles all user interface logic
  └── Creates buttons, input fields, and result table
  └── Responds to user actions (Search, Browse, Clear)
  └── Calls search.c when the user triggers a search

search.c
  └── Accepts a directory path and a search term
  └── Recursively walks through all subdirectories
  └── Checks each file/folder name for a match (case-insensitive)
  └── Returns results as a linked list

utils.c
  └── str_contains_ci()  — case-insensitive substring check
  └── to_lowercase()     — converts a string to lowercase
  └── format_size()      — formats a byte count as B / KB / MB
```

---

## How It Works

### Search Algorithm

1. The user provides a **root directory** and a **search term**
2. `search_by_name()` in `search.c` opens the root directory using the Windows `FindFirstFileA` API
3. For every entry found:
   - If it is a **folder**: check if the folder name contains the search term, then recurse into it
   - If it is a **file**: check if the file name contains the search term
4. Every match is added to a **singly linked list** (`ResultNode`)
5. After the search completes, `gui.c` reads the linked list and populates the `ListView` table
6. Memory is freed after the results are displayed or when the user clears the list

### String Matching

Matching is done using a **case-insensitive contains** check. Both the file name and the search term are converted to lowercase before comparison. This means searching for `Photo` will also match `photo_2024.jpg`, `PHOTO_backup`, and `my_photos`.

---

## Tech Stack

| Component        | Technology                        |
|------------------|-----------------------------------|
| Language         | C (C99 standard)                  |
| GUI Framework    | Windows API (WinAPI)              |
| UI Controls      | LISTVIEW, EDIT, BUTTON (Win32)    |
| File System API  | FindFirstFileA / FindNextFileA    |
| Folder Dialog    | SHBrowseForFolderA (Shell API)    |
| Compiler         | GCC via MinGW                     |
| Build System     | Windows Batch Script (.bat)       |
| Target OS        | Windows 7 / 8 / 10 / 11          |

---

## Known Limitations

- **Windows only** — uses WinAPI exclusively, not cross-platform
- **No file content search** — only searches by file/folder name
- **No export feature** — results cannot be saved to a file
- Very large directories with thousands of files may take a few seconds to scan

---

## Future Improvements

- Add extension-based filtering (e.g., search only `.pdf` or `.txt` files)
- Add a progress indicator while search is running
- Allow exporting search results to a `.txt` or `.csv` file
- Add date modified / file size filters
- Support searching by partial extension

---

## License

Free to use, modify, and distribute.

