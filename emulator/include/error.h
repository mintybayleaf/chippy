#ifndef CHIPPY_ERROR_H
#define CHIPPY_ERROR_H

#include <stdlib.h>
#include <stdio.h>

inline void error(const char* message) {
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

#endif