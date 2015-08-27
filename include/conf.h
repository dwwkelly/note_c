#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <json-c/json.h>
#include "parse.h"

typedef struct _Config {
    int daemonize;
    char* conf_file;
    size_t conf_file_len;
    char* address;
    size_t address_len;
    unsigned int port;
    int debug;
} Config;

Config* init_config();
int free_config(Config* conf);
int read_config(cli_options* options, Config* config);
int print_config(Config* conf);

#endif
