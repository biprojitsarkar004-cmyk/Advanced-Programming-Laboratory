#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/utils.h"

// Case-insensitive substring check
int str_contains_ci(const char *haystack, const char *needle) {
    if (!haystack || !needle) return 0;
    char h[1024], n[256];
    strncpy(h, haystack, sizeof(h) - 1);
    strncpy(n, needle,   sizeof(n) - 1);
    h[sizeof(h)-1] = '\0';
    n[sizeof(n)-1] = '\0';
    to_lowercase(h);
    to_lowercase(n);
    return strstr(h, n) != NULL;
}

// String ke lowercase e convert kore
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower((unsigned char)str[i]);
}

// File size ke readable format e dekhay
void format_size(long size, char *buf, int buf_len) {
    if (size < 0)
        snprintf(buf, buf_len, "—");
    else if (size < 1024)
        snprintf(buf, buf_len, "%ld B", size);
    else if (size < 1024 * 1024)
        snprintf(buf, buf_len, "%.1f KB", size / 1024.0);
    else
        snprintf(buf, buf_len, "%.1f MB", size / (1024.0 * 1024.0));
}
