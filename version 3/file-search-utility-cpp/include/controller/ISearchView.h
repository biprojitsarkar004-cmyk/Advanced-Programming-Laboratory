#pragma once

#include "../model/SearchModel.h"
#include <cstddef>
#include <string>
#include <vector>

class ISearchView {
public:
    virtual ~ISearchView() = default;

    /*
     * MVC note:
     * This interface is the bridge from Controller to View.
     * SearchController does not directly depend on MainWindow.
     * It only knows that "some View" can provide input and show output.
     */

    // Input methods: Controller uses these to read data from the View.
    virtual std::string directoryText() const = 0;
    virtual std::string queryText() const = 0;
    virtual SearchMode selectedSearchMode() const = 0;

    // Output methods: Controller uses these to update the View.
    virtual void showWarning(const std::string& message) = 0;
    virtual void setBusy(bool busy) = 0;
    virtual void showResults(const std::vector<SearchResult>& results) = 0;
    virtual void showResultCount(std::size_t count) = 0;
    virtual void setStatusText(const std::string& text) = 0;
};
