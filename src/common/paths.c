#include "paths.h"

char* join_paths(char* destination, const char* path1, const char* path2)
{
    if(path1 == NULL && path2 == NULL) {
            strcpy(destination, "");
        }
    else if(path2 == NULL || !path2[0]) {
            strcpy(destination, path1);
        }
    else if(path1 == NULL || !path2[0]) {
            strcpy(destination, path2);
        }
    else {
            char directory_separator[] = "/";
            const char* last_char = path1 + (strlen(path1) - 1);
            int append_directory_separator = 0;

            if(strcmp(last_char, directory_separator) != 0) {
                        append_directory_separator = 1;
                    }
            strcpy(destination, path1);
            if(last_char != directory_separator)
                strcat(destination, directory_separator);
            strcat(destination, path2);
        }

    return destination;
}

int expand_path(char* path, char* buf, size_t buf_size) {

    if(*path != '~'){
        strncpy(path, buf, buf_size);
        return 0;
    }

    char* home_dir = getenv("HOME");
    if(home_dir == NULL) {
        return 1;
    }

    join_paths(buf, home_dir, path+1);
    return 0;
}
