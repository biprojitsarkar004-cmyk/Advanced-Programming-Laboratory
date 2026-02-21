#include <windows.h>
#include <shlobj.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include "../include/gui.h"
#include "../include/search.h"
#include "../include/utils.h"

// পুরনো MinGW এর জন্য manually define করা
#ifndef LVM_SETEXTENDEDLISTVIEWSTYLE
#define LVM_SETEXTENDEDLISTVIEWSTYLE (0x1000 + 54)
#endif
#ifndef LVS_EX_FULLROWSELECT
#define LVS_EX_FULLROWSELECT  0x00000020
#endif
#ifndef LVS_EX_GRIDLINES
#define LVS_EX_GRIDLINES      0x00000001
#endif

#define COLOR_BG     RGB(245, 247, 250)
#define COLOR_ACCENT RGB(37,  99,  235)
#define COLOR_WHITE  RGB(255, 255, 255)
#define COLOR_TEXT   RGB(30,  41,  59)

static HWND hInputName, hInputFolder, hBtnSearch, hBtnBrowse;
static HWND hListView, hLabelStatus, hBtnClear;
static HFONT hFontTitle, hFontNormal, hFontBold;
static HBRUSH hBrushBg, hBrushAccent;
static ResultNode *g_results = NULL;

void gui_init_listview(HWND hList) {
    LVCOLUMNA col;
    ZeroMemory(&col, sizeof(col));
    col.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

    col.cx = 65;  col.pszText = "Type";  col.iSubItem = 0; ListView_InsertColumn(hList, 0, &col);
    col.cx = 420; col.pszText = "Path";  col.iSubItem = 1; ListView_InsertColumn(hList, 1, &col);
    col.cx = 100; col.pszText = "Size";  col.iSubItem = 2; ListView_InsertColumn(hList, 2, &col);

    SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void gui_populate_results(HWND hList, ResultNode *results, int *count) {
    ListView_DeleteAllItems(hList);
    *count = 0;
    int i = 0;
    for (ResultNode *r = results; r != NULL; r = r->next) {
        LVITEMA item;
        ZeroMemory(&item, sizeof(item));
        item.mask     = LVIF_TEXT;
        item.iItem    = i;
        item.iSubItem = 0;
        item.pszText  = r->type;
        ListView_InsertItem(hList, &item);
        ListView_SetItemText(hList, i, 1, r->path);
        char size_buf[32];
        format_size(r->size, size_buf, sizeof(size_buf));
        ListView_SetItemText(hList, i, 2, size_buf);
        i++;
        (*count)++;
    }
}

void gui_set_status(HWND hStatus, int count) {
    char buf[128];
    if (count == 0)
        snprintf(buf, sizeof(buf), "Kono file/folder pawa jay ni.");
    else
        snprintf(buf, sizeof(buf), "Motot %d ta file/folder pawa geche!", count);
    SetWindowTextA(hStatus, buf);
}

void gui_clear_results(HWND hList) {
    ListView_DeleteAllItems(hList);
}

static void do_search(HWND hwnd) {
    char name[256]   = {0};
    char folder[512] = {0};
    GetWindowTextA(hInputName,   name,   sizeof(name));
    GetWindowTextA(hInputFolder, folder, sizeof(folder));

    if (strlen(name) == 0) {
        MessageBoxA(hwnd, "File/Folder er naam likhun!", "Oops!", MB_ICONWARNING | MB_OK);
        return;
    }
    if (strlen(folder) == 0) {
        MessageBoxA(hwnd, "Folder select korun!", "Oops!", MB_ICONWARNING | MB_OK);
        return;
    }

    if (g_results) { free_results(g_results); g_results = NULL; }
    SetWindowTextA(hLabelStatus, "Khoja hocche... ektu opekkha korun...");
    UpdateWindow(hwnd);

    g_results = search_by_name(folder, name);

    int count = 0;
    gui_populate_results(hListView, g_results, &count);
    gui_set_status(hLabelStatus, count);
}

static void do_browse(HWND hwnd) {
    BROWSEINFOA bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = hwnd;
    bi.lpszTitle = "Folder select korun:";
    bi.ulFlags   = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (pidl) {
        char path[512];
        if (SHGetPathFromIDListA(pidl, path))
            SetWindowTextA(hInputFolder, path);
        CoTaskMemFree(pidl);
    }
}

static void paint_header(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rcHeader = {0, 0, 700, 68};
    FillRect(hdc, &rcHeader, hBrushAccent);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, COLOR_WHITE);
    SelectObject(hdc, hFontTitle);
    RECT rcText = {20, 10, 660, 40};
    DrawTextA(hdc, "  File Search Utility", -1, &rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hdc, hFontNormal);
    SetTextColor(hdc, RGB(186, 230, 253));
    RECT rcSub = {22, 42, 660, 64};
    DrawTextA(hdc, "  Naam diye file & folder khujun — sob subfolder e khujbe", -1, &rcSub, DT_LEFT | DT_SINGLELINE);

    EndPaint(hwnd, &ps);
}

static void create_controls(HWND hwnd) {
    hFontTitle  = CreateFontA(20, 0, 0, 0, FW_BOLD,   0,0,0, DEFAULT_CHARSET, 0,0, CLEARTYPE_QUALITY, 0, "Segoe UI");
    hFontNormal = CreateFontA(14, 0, 0, 0, FW_NORMAL, 0,0,0, DEFAULT_CHARSET, 0,0, CLEARTYPE_QUALITY, 0, "Segoe UI");
    hFontBold   = CreateFontA(14, 0, 0, 0, FW_BOLD,   0,0,0, DEFAULT_CHARSET, 0,0, CLEARTYPE_QUALITY, 0, "Segoe UI");
    hBrushBg     = CreateSolidBrush(COLOR_BG);
    hBrushAccent = CreateSolidBrush(COLOR_ACCENT);

    int y = 82;

    HWND h = CreateWindowA("STATIC", "File / Folder Naam:",
        WS_CHILD|WS_VISIBLE, 20, y, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(h, WM_SETFONT, (WPARAM)hFontBold, TRUE);

    hInputName = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
        WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,
        20, y+22, 390, 28, hwnd, (HMENU)ID_INPUT_NAME, NULL, NULL);
    SendMessage(hInputName, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

    hBtnSearch = CreateWindowA("BUTTON", "Search",
        WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
        420, y+22, 100, 28, hwnd, (HMENU)ID_BTN_SEARCH, NULL, NULL);
    SendMessage(hBtnSearch, WM_SETFONT, (WPARAM)hFontBold, TRUE);

    hBtnClear = CreateWindowA("BUTTON", "Clear",
        WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
        530, y+22, 80, 28, hwnd, (HMENU)ID_BTN_CLEAR, NULL, NULL);
    SendMessage(hBtnClear, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

    y += 62;

    HWND h2 = CreateWindowA("STATIC", "Kothay Khujbo (Folder):",
        WS_CHILD|WS_VISIBLE, 20, y, 220, 20, hwnd, NULL, NULL, NULL);
    SendMessage(h2, WM_SETFONT, (WPARAM)hFontBold, TRUE);

    hInputFolder = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "C:\\",
        WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,
        20, y+22, 470, 28, hwnd, (HMENU)ID_INPUT_FOLDER, NULL, NULL);
    SendMessage(hInputFolder, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

    hBtnBrowse = CreateWindowA("BUTTON", "Browse...",
        WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
        500, y+22, 110, 28, hwnd, (HMENU)ID_BTN_BROWSE, NULL, NULL);
    SendMessage(hBtnBrowse, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

    y += 68;

    HWND hSep = CreateWindowA("STATIC",
        "─────────────────────────────────── Result ──────────────────────────────────",
        WS_CHILD|WS_VISIBLE, 20, y, 630, 16, hwnd, NULL, NULL, NULL);
    SendMessage(hSep, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

    y += 20;

    hListView = CreateWindowExA(WS_EX_CLIENTEDGE, WC_LISTVIEWA, "",
        WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_SHOWSELALWAYS,
        20, y, 630, 290, hwnd, (HMENU)ID_LISTVIEW, NULL, NULL);
    SendMessage(hListView, WM_SETFONT, (WPARAM)hFontNormal, TRUE);
    gui_init_listview(hListView);

    y += 300;

    hLabelStatus = CreateWindowA("STATIC",
        "Naam likhun, folder select korun, tarpor Search click korun.",
        WS_CHILD|WS_VISIBLE|SS_LEFT,
        20, y, 630, 22, hwnd, (HMENU)ID_LABEL_STATUS, NULL, NULL);
    SendMessage(hLabelStatus, WM_SETFONT, (WPARAM)hFontNormal, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            create_controls(hwnd);
            return 0;

        case WM_PAINT:
            paint_header(hwnd);
            return 0;

        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLOREDIT: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, COLOR_BG);
            SetTextColor(hdc, COLOR_TEXT);
            return (LRESULT)hBrushBg;
        }

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BTN_SEARCH: do_search(hwnd); break;
                case ID_BTN_BROWSE: do_browse(hwnd); break;
                case ID_BTN_CLEAR:
                    gui_clear_results(hListView);
                    SetWindowTextA(hInputName, "");
                    SetWindowTextA(hLabelStatus, "Cleared.");
                    if (g_results) { free_results(g_results); g_results = NULL; }
                    break;
            }
            return 0;

        case WM_DESTROY:
            if (g_results) free_results(g_results);
            DeleteObject(hFontTitle);
            DeleteObject(hFontNormal);
            DeleteObject(hFontBold);
            DeleteObject(hBrushBg);
            DeleteObject(hBrushAccent);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}
