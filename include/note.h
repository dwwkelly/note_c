#include <json-c/json.h>

/*
 *
 */
int note_search_by_body(int* ids, char* body);

/*
 *
 */
int note_search_by_tags(int* ids, char** tags, size_t n_tags);

/*
 *
 */
int note_search_by_time(int* ids, char** tags, size_t n_tags);

/*
 *
 */
int note_add(json_object* jobj);

/*
 *
 */
int note_get(json_object* jobj, int id);
