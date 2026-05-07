#pragma once

#include "../utils/Win32Compat.h"
#include <string>
#include <windows.h>

/*
 * SearchResult.h - Model (SRP)
 *
 * Single Responsibility:
 * This struct only holds data for one matched file.
 * It has no search logic and no display logic.
 *
 * MVC note:
 * SearchResult is part of the Model because it represents application data.
 * The View displays this data, but the View does not own the data meaning.
 */
struct SearchResult {
    std::string fullPath;       // e.g. C:\Users\...\notes.txt
    std::string fileName;       // e.g. notes.txt
    std::string extension;      // e.g. .txt
    std::string sizeFormatted;  // e.g. 12 KB
    LONGLONG    sizeBytes = 0;
};
