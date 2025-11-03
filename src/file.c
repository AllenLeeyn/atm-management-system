#include "header.h"

FILE *openFileOrExit(const char *filename, const char *mode) {
    FILE *fp = fopen(filename, mode);
    if (!fp) {
        printf("Error! Could not open file: %s\n", filename);
        exit(1);
    }
    return fp;
}