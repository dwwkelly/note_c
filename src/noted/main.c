#include "parse.h"
#include "conf.h"

int main(int argc, char *argv[])
{
    int rv = 0;
    cli_options* options = init_cli_options();

    rv = parse_cli(argc, argv, options);
    if (rv < 0) {
        printf("Error parsing config file\n");
        exit(EXIT_FAILURE);
    }

    Config* conf = init_config();
    read_config(options, conf);

    if(options->print) {
        print_config(conf);
        free_config(conf);
        free_cli_options(options);
        exit(EXIT_SUCCESS);
    }

    free_config(conf);
    free_cli_options(options);

    return 0;
}
