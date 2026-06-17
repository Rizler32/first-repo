#include "strings.h"

int string_length(const char* str) {
    // basterebbe fare strlen(str) di <string.h>
    int count = 0;
    while (str[count] != '\0') count++;
    return count;
}
