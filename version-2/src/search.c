#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/search.h"
#include "../include/utils.h"

// Linked list e new node add kore
static ResultNode* create_node(const char *path, const char *type, long size) {
    ResultNode *node = (ResultNode*)malloc(sizeof(ResultNode));
    if (!node) return NULL;
    strncpy(node->path, path, sizeof(node->path) - 1);
    strncpy(node->type, type, sizeof(node->type) - 1);
    node->path[sizeof(node->path)-1] = '\0';
    node->type[sizeof(node->type)-1] = '\0';
    node->size = size;
    node->next = NULL;
    return node;
}

// Recursive search function (Windows FindFirstFile API use kore)
static void search_recursive(const char *dir, const char *name,
                              ResultNode **head, ResultNode **tail) {
    char pattern[1024];
    snprintf(pattern, sizeof(pattern), "%s\\*", dir);

    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(pattern, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        // . and .. skip koro
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s\\%s", dir, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // FOLDER — naam match korle add koro
            if (str_contains_ci(fd.cFileName, name)) {
                ResultNode *node = create_node(full_path, "FOLDER", -1);
                if (node) {
                    if (!*head) *head = *tail = node;
                    else { (*tail)->next = node; *tail = node; }
                }
            }
            // Sub-folder e dhuko
            search_recursive(full_path, name, head, tail);

        } else {
            // FILE — naam match korle add koro
            if (str_contains_ci(fd.cFileName, name)) {
                long size = ((long)fd.nFileSizeHigh * (MAXDWORD + 1LL)) + fd.nFileSizeLow;
                ResultNode *node = create_node(full_path, "FILE", size);
                if (node) {
                    if (!*head) *head = *tail = node;
                    else { (*tail)->next = node; *tail = node; }
                }
            }
        }

    } while (FindNextFileA(hFind, &fd));

    FindClose(hFind);
}

// Public function — search kore result list return kore
ResultNode* search_by_name(const char *dir, const char *name) {
    ResultNode *head = NULL, *tail = NULL;
    search_recursive(dir, name, &head, &tail);
    return head;
}

// Memory free kore
void free_results(ResultNode *head) {
    while (head) {
        ResultNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}
