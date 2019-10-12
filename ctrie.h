#ifndef __CTRIE_H__
#define __CTRIE_H__

#include "ctrie_config.h"

struct ctrie_t;
typedef struct ctrie_t ctrie;


ctrie* ctrie_create();

void ctrie_destroy(ctrie* map);

void ctrie_add(ctrie* map, char* key, ctrie_value_t* value);

void ctrie_remove(ctrie* map, char* s);

ctrie_value_t* ctrie_lookup(ctrie* map, char* s);


//======= TESTING FUNCTIONS ================
size_t ctrie_test_value(ctrie* map);
ctrie* ctrie_create_test();


#endif // !__CTRIE_H__

