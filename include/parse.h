#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include "paths.h"

typedef struct _cli_options {
    int daemonize;
    char* conf_file;
    size_t conf_file_len;
    int print;
    int debug;
} cli_options;

cli_options* init_cli_options();
int free_cli_options(cli_options* options);
int parse_cli(int argc, char** argv, cli_options* options);
int print_help(char** argv);

#endif
