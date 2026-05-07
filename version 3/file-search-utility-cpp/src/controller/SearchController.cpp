#include "../../include/controller/SearchController.h"
#include <sstream>

SearchController::SearchController(ISearchView& view)
    : view_(view) {}

void SearchController::runSearch() {
    /*
     * MVC flow for Search:
     * 1. Controller asks the View for user input.
     * 2. Controller validates that input.
     * 3. Controller asks the Model to perform the search.
     * 4. Controller tells the View to display the Model result.
     */
    const std::string dir = view_.directoryText();
    const std::string query = view_.queryText();

    // Validation belongs in the Controller because it decides the workflow.
    if (dir.empty()) {
        view_.showWarning("Please select a directory first.");
        return;
    }

    if (query.empty()) {
        view_.showWarning("Please enter a search query.");
        return;
    }

    view_.setStatusText("Searching...");
    view_.setBusy(true);

    // Model does the actual application work and stores the result state.
    const auto& results = model_.search(dir, query, view_.selectedSearchMode());

    view_.setBusy(false);

    // View only displays what the Controller sends to it.
    view_.showResults(results);
    view_.showResultCount(model_.resultCount());

    std::ostringstream oss;
    oss << "Done - " << model_.resultCount() << " file(s) found for \""
        << query << "\" [" << model_.activeStrategyName() << "]";
    view_.setStatusText(oss.str());
}

void SearchController::clearResults() {
    /*
     * MVC flow for Clear:
     * Controller clears the Model first, then tells the View to show
     * the empty result state.
     */
    model_.clear();
    view_.showResults(model_.results());
    view_.showResultCount(0);
    view_.setStatusText("Cleared.");
}
