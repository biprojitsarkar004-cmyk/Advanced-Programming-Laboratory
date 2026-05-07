#pragma once

#include "IWindow.h"
#include "ResultsListView.h"
#include "../controller/ISearchView.h"
#include "../controller/SearchController.h"
#include <memory>
#include <string>
#include <vector>

constexpr int ID_EDIT_DIR       = 101;
constexpr int ID_EDIT_QUERY     = 102;
constexpr int ID_BTN_BROWSE     = 103;
constexpr int ID_BTN_SEARCH     = 104;
constexpr int ID_BTN_CLEAR      = 105;
constexpr int ID_LISTVIEW       = 106;
constexpr int ID_STATIC_STATUS  = 107;
constexpr int ID_RADIO_NAME     = 108;
constexpr int ID_RADIO_EXT      = 109;
constexpr int ID_RADIO_CONTENT  = 110;
constexpr int ID_STATIC_COUNT   = 111;

constexpr int WINDOW_WIDTH  = 820;
constexpr int WINDOW_HEIGHT = 600;

/*
 * MVC View:
 * MainWindow is the View layer of this project.
 * It creates the Win32 controls, reads user input, and displays output.
 * It does not perform the search workflow by itself.
 * Search and Clear actions are delegated to SearchController.
 */
class MainWindow : public IWindow, public ISearchView {
public:
    MainWindow();

    // IWindow methods: used by main.cpp to create/show the application window.
    bool create(HINSTANCE hInstance, int nCmdShow) override;
    HWND handle() const override { return hwnd_; }

    // Win32 message router. It forwards Windows messages to this object.
    static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

    /*
     * ISearchView methods:
     * These methods are called by SearchController.
     * They let the Controller read from and write to the View
     * without knowing Win32 control details.
     */
    std::string directoryText() const override;
    std::string queryText() const override;
    SearchMode selectedSearchMode() const override;
    void showWarning(const std::string& message) override;
    void setBusy(bool busy) override;
    void showResults(const std::vector<SearchResult>& results) override;
    void showResultCount(std::size_t count) override;
    void setStatusText(const std::string& text) override;

private:
    HWND hwnd_ = nullptr;
    HINSTANCE hInst_ = nullptr;
    ResultsListView listView_;

    // View owns the Controller and delegates user actions to it.
    std::unique_ptr<SearchController> controller_;

    // Internal Win32 message handling helpers.
    LRESULT handleMessage(HWND, UINT, WPARAM, LPARAM);
    void onCreate(HWND hwnd);
    void onCommand(WPARAM wParam);

    // View-only helper methods.
    void browseFolder();
    std::string getDlgText(int ctrlId) const;
};
