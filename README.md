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

Difference Between Version 1 and Version 2

Overview
Version 1 is a single-file implementation where GUI, search logic, and utility functions are combined in one source file.
Version 2 is a modular implementation where responsibilities are separated into multiple files (main, GUI, search, utilities).

1. Project Structure

Version 1:

* Entire program exists in one file.
* GUI logic, search logic, and helper functions are mixed together.
* High coupling between components.

Version 2:

* Divided into multiple source files:

  * main (program entry and window registration)
  * gui (all UI-related logic)
  * search (recursive search and result creation)
  * utils (string utilities and formatting)
* Clear separation of responsibilities.
* Lower coupling and better organization.

2. Separation of Concerns

Version 1:

* Search functions directly interact with GUI elements.
* Search logic depends on UI components.
* Hard to reuse search logic outside the GUI.

Version 2:

* Search layer returns structured results.
* GUI layer only displays results.
* Search logic is independent of UI.
* Code is reusable in other contexts (CLI, API, library).

3. Data Handling

Version 1:

* Uses simple buffers and global variables.
* Stores limited result information.
* No structured data model.

Version 2:

* Uses a linked list (ResultNode) to store:

  * Path
  * Type (FILE or FOLDER)
  * Size
* Supports multiple results properly.
* More flexible and extendable.

4. Memory Management

Version 1:

* Mostly static memory.
* Minimal dynamic allocation.
* Simpler but less scalable.

Version 2:

* Uses dynamic memory (malloc).
* Provides proper cleanup function (free_results).
* More suitable for large and scalable applications.

5. User Interface

Version 1:

* Uses basic ListBox.
* Minimal styling.
* Limited result visualization.

Version 2:

* Uses ListView in report mode.
* Multiple columns (Type, Path, Size).
* Gridlines and full row selection.
* Custom fonts and colors.
* Status updates and clear functionality.
* More polished and user-friendly interface.

6. Maintainability

Version 1:

* Harder to debug because everything is in one file.
* Changes in one area may affect unrelated parts.
* Difficult to extend cleanly.

Version 2:

* Easier to debug due to modular separation.
* Changes are isolated within specific files.
* Cleaner and more maintainable structure.

7. Scalability

Version 1:

* Difficult to extend with new features.
* Adding sorting, filtering, or exporting would require significant refactoring.

Version 2:

* Easier to extend.
* Can add features like sorting, filtering, exporting, or threading more cleanly.
* Better foundation for future growth.

8. Code Quality Level

Version 1:

* Suitable for learning or small prototype.
* Functional but tightly coupled.

Version 2:

* Structured and closer to production-level design.
* Demonstrates better architectural thinking.
* More aligned with professional software development practices.

Final Conclusion

Version 1 demonstrates functional implementation in a simple structure.
Version 2 improves significantly by introducing modular architecture, structured data handling, better separation of concerns, improved UI design, and enhanced maintainability.

Overall, Version 2 is more scalable, maintainable, reusable, and closer to professional software engineering standards.

