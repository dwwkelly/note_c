#include "conf.h"

/* Keep these functions private to this file */
int process_config_string(Config* config, char* key, struct json_object* val);
int process_config_int(Config* config, char* key, struct json_object* val);
int process_config_bool(Config* config, char* key, struct json_object* val);
int process_config_double(Config* config, char* key, struct json_object* val);
int process_config_object(Config* config, char* key, struct json_object* val);
int process_config_null(Config* config, char* key, struct json_object* val);
int process_config_array(Config* config, char* key, struct json_object* val);

Config* init_config(){

    Config* config = (Config*) malloc(sizeof(Config));

    config->daemonize = 0;
    config->debug = 0;
    config->conf_file_len = 0;
    config->conf_file = NULL;
    config->address = NULL;
    config->address_len = 0;
    config->port = 0;
    config->debug = 0;

    return config;
}

int free_config(Config* conf){

    if (conf == NULL){
        return -1;
    }

    if (conf->conf_file != NULL){
        free((void*)conf->conf_file);
        conf->conf_file = NULL;
    }

    if (conf->address != NULL){
        free((void*)conf->address);
        conf->address = NULL;
    }

    free((void*)conf);
    conf = NULL;

    return 0;
}

int print_config(Config* conf) {

    if (conf == NULL) {
        return -1;
    }

    if (conf->conf_file != NULL) {
        printf("Config file name %s\n", conf->conf_file);
    } else {
        printf("Config Filename is NULL\n");
    }
    printf("Config file length %lu\n", conf->conf_file_len);

    if (conf->address != NULL) {
        printf("Address: %s\n", conf->address);
    } else {
        printf("Address is NULL\n");
    }
    printf("Address length: %lu\n", conf->address_len);

    printf("Port: %u\n", conf->port);

    if(conf->daemonize) {
        printf("Daemonize is True\n");
    } else {
        printf("Daemonize is False\n");
    }


    return 0;
}

int read_config(cli_options* options, Config* config){

    if (options == NULL) {
        return -1;
    }

    if (config == NULL) {
        return -1;
    }

    if (options->conf_file == NULL) {
        return -1; // No config file to read!
    }

    config->debug = options->debug;

    size_t buf_len = 131072;
    char buf[buf_len];
    memset(buf, buf_len, 0);
    FILE* fd = fopen(options->conf_file, "r");
    if (fd == NULL) {
        return -1;
    }

    size_t bytes = fread(buf, sizeof(char), buf_len, fd);
    if (bytes == 0) {
        return -1;
    }
    fclose(fd);

    json_object* jobj = json_tokener_parse(buf);
    if (jobj == NULL) {
        return -1;
    }
    enum json_type type = json_object_get_type(jobj);

    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_string:
                process_config_string(config, key, val);
                break;
            case (json_type_null):
                process_config_null(config, key, val);
                break;
            case (json_type_boolean):
                process_config_bool(config, key, val);
                break;
            case (json_type_double):
                process_config_double(config, key, val);
                break;
            case (json_type_object):
                process_config_object(config, key, val);
                break;
            case (json_type_int):
                process_config_int(config, key, val);
                break;
            case (json_type_array):
                process_config_array(config, key, val);
                break;
        }
     }

    json_object_put(jobj);

    return 0;
}

int process_config_string(Config* config, char* key, struct json_object* val) {
    const char* val_str = json_object_get_string(val);
    if(config->debug){
        printf("type: json_type_string\n");
        printf("key: %s\n", key);
        printf("value: %s\n", val_str);
    }

    if (strncmp(key, "notesfile", 9) == 0) {
        size_t len = strlen(val_str);
        config->conf_file_len = len;

        config->conf_file = (char*) malloc((len + 1) * sizeof(char));
        strncpy(config->conf_file, val_str, len + 1);
    }

    if (strncmp(key, "address", 15) == 0) {  // Longest char* IPv4 address is 15 bytes
        size_t len = strlen(val_str);
        config->address_len = len;

        config->address = (char*) malloc((len + 1) * sizeof(char));
        strncpy(config->address, val_str, len + 1);
    }

    return 0;
}

int process_config_int(Config* config, char* key, struct json_object* val) {
    int val_int= json_object_get_int(val);
    if(config->debug){
        printf("type: json_type_int\n");
        printf("key: %s\n", key);
        printf("value: %d\n", val_int);
    }

    if (strncmp(key, "port", 4) == 0) {
        config->port = val_int;
    }

    return 0;
}

int process_config_bool(Config* config, char* key, struct json_object* val) {
    json_bool val_bool= json_object_get_int(val);
    if(config->debug){
        printf("type: json_type_bool\n");
        printf("key: %s\n", key);
        if (val_bool) {
            printf("value: True\n");
        } else {
            printf("value: False\n");
        }
    }

    if (strncmp(key, "daemonize", 9) == 0) {
        config->daemonize = val_bool;
    }

    return 0;
}


int process_config_double(Config* config, char* key, struct json_object* val) {
    double val_double = json_object_get_double(val);

    if (val_double) {}  // placeholder

    return 0;
}

int process_config_object(Config* config, char* key, struct json_object* val) {
    struct lh_table* val_object = json_object_get_object(val);

    if (val_object == NULL){
        return -1;
    }

    return 0;
}

int process_config_null(Config* config, char* key, struct json_object* val) {

    return 0;
}

int process_config_array(Config* config, char* key, struct json_object* val) {
    struct array_list* array = json_object_get_array(val);

    if (array == NULL) {
        return -1;
    }

    return 0;
}
