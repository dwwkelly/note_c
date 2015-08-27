#include <string.h>
#include "parse.h"


cli_options* init_cli_options() {

    cli_options* options = (cli_options*) malloc(sizeof(cli_options));
    options->conf_file = NULL;
    options->conf_file_len = 0;
    options->daemonize = 0;
    options->print = 0;
    options->debug = 0;

    return options;
}

int free_cli_options(cli_options* options) {

    if(options->conf_file != NULL) {
        free((void*)options->conf_file);
        options->conf_file = NULL;
    }

    free((void*)options);
    options = NULL;

    return 0;
}

int parse_cli(int argc, char** argv, cli_options* options) {

    int opt = 0;
    size_t buf_len = 8192;
    char buf[buf_len];
    size_t malloc_size = buf_len;
    memset(buf, 0, buf_len);

    if (options == NULL) {
        return -1;
    }

    while ((opt = getopt(argc, argv, "pDhdc:")) != -1) {
        switch (opt) {
            case 'p':
                options->print = 1;
                break;
            case 'D':
                options->debug = 1;
                break;
            case 'd':
                options->daemonize = 1;
                break;
            case 'c':
                expand_path(buf, optarg, buf_len);
                options->conf_file_len = strnlen(buf, buf_len);
                malloc_size = sizeof(char) * (size_t) (options->conf_file_len + 1);
                options->conf_file = (char*) malloc(malloc_size);
                memset(options->conf_file, 0, malloc_size);
                strncpy(options->conf_file, buf, malloc_size);
                break;
            case 'h':
                print_help(argv);
                exit(EXIT_SUCCESS);
            default: /* '?' */
                print_help(argv);
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}

int print_help(char** argv){
    fprintf(stderr, "Usage: %s [-d] [-p] [-D] [-h] [-c config_file]\n", argv[0]);
    return 0;
}

int print_options(cli_options* options) {
    printf("Config File: %s\n", options->conf_file);
    printf("Config File Len %lu\n", options->conf_file_len);
    if (options->daemonize)
        printf("Daemonize: True\n");
    else
        printf("Daemonize: False\n");

    return 0;
}
