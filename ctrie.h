#ifndef __CTRIE_H__
#define __CTRIE_H__

#include "ctrie_config.h"

struct ctrie_t;
typedef struct ctrie_t ctrie;


ctrie* ctrie_create();

void ctrie_destroy(ctrie* map);

void ctrie_add(ctrie* map, const char* key, const ctrie_value_t value);

void ctrie_remove(ctrie* map, const char* key);

ctrie_value_t ctrie_lookup(const ctrie* map, const char* key);


#endif // !__CTRIE_H__

