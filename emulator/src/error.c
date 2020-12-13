#include "error.h"



void error(const char* msg) {
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}
