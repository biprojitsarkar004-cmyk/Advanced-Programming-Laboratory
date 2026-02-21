#ifndef GUI_H
#define GUI_H

#include <windows.h>
#include "search.h"

// Window control IDs
#define ID_INPUT_NAME     101
#define ID_INPUT_FOLDER   102
#define ID_BTN_SEARCH     103
#define ID_BTN_BROWSE     104
#define ID_LISTVIEW       105
#define ID_LABEL_STATUS   106
#define ID_BTN_CLEAR      107

// Main window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// GUI helper functions
void gui_init_listview(HWND hList);
void gui_populate_results(HWND hList, ResultNode *results, int *count);
void gui_set_status(HWND hStatus, int count);
void gui_clear_results(HWND hList);

#endif

