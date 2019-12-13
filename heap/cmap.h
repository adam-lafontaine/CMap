#ifndef CMAP_HEAP_H__
#define CMAP_HEAP_H__

#include "cmap_config.h"

typedef struct cmap_t cmap;

typedef struct cmap_pair_t {
	char* key;
	cmap_value_t value;
} cmap_pair;


cmap* cmap_create();

void cmap_destroy(cmap* map);

void cmap_add(cmap* map, const char* key, const cmap_value_t value);

void cmap_erase(cmap* map, const char* key);

cmap_pair* cmap_remove(cmap* map, const char* key);

cmap_pair* cmap_get(cmap* map, const char* key);

cmap_pair* cmap_get_first(cmap* map);

cmap_pair* cmap_get_next(cmap* map, const char* key);

bool cmap_empty(cmap* map);



#endif // !__CMAP_H__

