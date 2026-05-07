#pragma once

#include "SearchResult.h"
#include <cstddef>
#include <string>
#include <vector>

enum class SearchMode {
    Name,
    Extension,
    Content
};

/*
 * MVC Model:
 * SearchModel contains application state and application logic.
 * It does not create buttons, windows, or message boxes.
 * It only knows how to search and remember the search results.
 */
class SearchModel {
public:
    // Performs search using the selected mode and stores the results.
    const std::vector<SearchResult>& search(const std::string& rootDir,
                                            const std::string& query,
                                            SearchMode mode);

    // Removes all stored search results.
    void clear();

    // Getter methods used by the Controller after search/clear.
    const std::vector<SearchResult>& results() const { return results_; }
    std::size_t resultCount() const { return results_.size(); }
    const std::string& activeStrategyName() const { return activeStrategyName_; }

private:
    // Model state: latest search result list.
    std::vector<SearchResult> results_;

    // Model state: name of the strategy used in the latest search.
    std::string activeStrategyName_;
};
