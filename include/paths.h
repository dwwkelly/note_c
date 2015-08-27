#ifndef PATHS_H
#define PATHS_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* join_paths(char* destination, const char* path1, const char* path2);
int expand_path(char* path, char* buf, size_t buf_size);

#endif
