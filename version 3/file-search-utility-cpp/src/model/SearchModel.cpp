#include "../../include/model/SearchModel.h"
#include "../../include/search/ContentSearchStrategy.h"
#include "../../include/search/ExtensionSearchStrategy.h"
#include "../../include/search/FileNameSearchStrategy.h"
#include "../../include/search/ISearchStrategy.h"
#include <memory>

namespace {
/*
 * Model helper:
 * This factory creates the correct search strategy based on SearchMode.
 * The View does not choose concrete strategy classes.
 * The Controller only passes the selected mode.
 * The Model decides which strategy object to use.
 */
std::unique_ptr<ISearchStrategy> makeStrategy(SearchMode mode) {
    switch (mode) {
        case SearchMode::Extension:
            return std::make_unique<ExtensionSearchStrategy>();
        case SearchMode::Content:
            return std::make_unique<ContentSearchStrategy>();
        case SearchMode::Name:
        default:
            return std::make_unique<FileNameSearchStrategy>();
    }
}
}

const std::vector<SearchResult>& SearchModel::search(const std::string& rootDir,
                                                     const std::string& query,
                                                     SearchMode mode) {
    // Create the correct strategy for the selected radio button mode.
    auto strategy = makeStrategy(mode);

    // Store strategy name so Controller can show it in the status text.
    activeStrategyName_ = strategy->name();

    // Run search and store the result inside the Model.
    results_ = strategy->search(rootDir, query);
    return results_;
}

void SearchModel::clear() {
    // Clear Model state. The View will be updated by the Controller.
    results_.clear();
    activeStrategyName_.clear();
}
