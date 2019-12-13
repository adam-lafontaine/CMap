#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cmap.h"

//======= NODE ==============================

struct cmap_node_t;
typedef struct cmap_node_t ct_node;

cmap_pair create_pair(const char* key, const cmap_value_t value) {

	cmap_pair pair;

	pair.key = (char*)key;
	pair.value = value;

	return pair;
}

