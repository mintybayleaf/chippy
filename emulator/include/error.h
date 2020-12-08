#ifndef CHIPPY_ERROR_H
#define CHIPPY_ERROR_H

#include <stdlib.h>
#include <stdio.h>

#define error(msg, ...) do { \
        fprintf(stderr, "\n%s:%d:  ", __FILE__, __LINE__); \
        fprintf(stderr, msg, __VA_ARGS__); \
    } while (0)

#endif