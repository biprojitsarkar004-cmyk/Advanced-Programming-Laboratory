#ifndef SEARCH_H
#define SEARCH_H

#include <windows.h>

// Search result list node
typedef struct ResultNode {
    char path[1024];
    char type[10];   // "FILE" or "FOLDER"
    long size;
    struct ResultNode *next;
} ResultNode;

// Search functions
ResultNode* search_by_name(const char *dir, const char *name);
void        free_results(ResultNode *head);

#endif
