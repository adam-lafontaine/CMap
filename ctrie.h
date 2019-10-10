#ifndef __CTRIE_H__
#define __CTRIE_H__

//#define CTRIE_KEY_LENGTH 2

struct ctrie_t;
typedef struct ctrie_t ctrie;
typedef int ctrie_value_t;

ctrie* ctrie_create();

void ctrie_destroy(ctrie* map);

void ctrie_add(ctrie* map, char* word);

void ctrie_remove(ctrie* map, char* word);


//======= TESTING FUNCTIONS ================
size_t ctrie_test_value(ctrie* map);
ctrie* ctrie_create_test();


#endif // !__CTRIE_H__

