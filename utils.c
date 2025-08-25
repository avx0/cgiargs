#include <string.h>
#include <stdlib.h>

char *
replace_substring(const char* str, const char* sub, const char* replacement)
{
    char* result;
    int i, count = 0;
    /* int newlen = strlen(str); */
    int oldlen = strlen(sub);
    int replen = strlen(replacement);

    // Count the number of occurrences of the substring
    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], sub) == &str[i]) {
            count++;
            i += oldlen - 1;
        }
    }

    // Allocate memory for the new string
    result = (char*)malloc(i + count * (replen - oldlen) + 1);

    i = 0;
    while (*str) {
        if (strstr(str, sub) == str) {
            strcpy(&result[i], replacement);
            i += replen;
            str += oldlen;
        } else {
            result[i++] = *str++;
        }
    }
    result[i] = '\0';

    return result;
}
