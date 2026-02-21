#ifndef UTILS_H
#define UTILS_H

int  str_contains_ci(const char *haystack, const char *needle);
void to_lowercase(char *str);
void format_size(long size, char *buf, int buf_len);

#endif
