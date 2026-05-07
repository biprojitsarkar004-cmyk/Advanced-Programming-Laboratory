#pragma once

#include "ISearchView.h"
#include "../model/SearchModel.h"

class SearchController {
public:
    explicit SearchController(ISearchView& view);

    // Called by the View when the user clicks the Search button.
    void runSearch();

    // Called by the View when the user clicks the Clear button.
    void clearResults();

private:
    /*
     * MVC note:
     * The Controller sits between View and Model.
     * view_ is used to read input and show output.
     * model_ is used to store/search application data.
     */
    ISearchView& view_;
    SearchModel model_;
};
