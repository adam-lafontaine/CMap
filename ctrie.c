#include <stdlib.h>

#include "ctrie.h"

static const char KEY_CHARS[] = { '0', '1' };

#define CTRIE_KEY_LENGTH sizeof(KEY_CHARS)



//======= NODE ==============================

typedef struct ctrie_node_t {
	ctrie* child[CTRIE_KEY_LENGTH];
	ctrie* parent;
	ctrie_value_t* value;
} ct_node;


ct_node* create_node() {
	ct_node* node = (ct_node*)malloc(sizeof(ct_node));

	if (node == NULL)
		return NULL;

	node->parent = NULL;
	node->value = NULL;

	size_t i = 0;
	while (i < CTRIE_KEY_LENGTH)
		node->child[i++] = NULL;

	return node;
}

void destroy_node(ct_node* node) {
	for (size_t i = 0; i < CTRIE_KEY_LENGTH; ++i)
		if (node->child[i] != NULL)
			destroy_node(node->child[i]);

	free(node);
}

void add_child(ct_node* node) {

}


//===== PUBLIC ==================================

struct ctrie_t {

	ct_node* root;
};


ctrie* ctrie_create() {
	ctrie* map = (ctrie*)malloc(sizeof(ctrie));

	if (map == NULL)
		return NULL;

	map->root = create_node();
	if (map->root == NULL) {
		free(map);
		return NULL;
	}

	return map;
}


void ctrie_destroy(ctrie* map) {

	if (map->root != NULL)
		destroy_node(map->root);

	free(map);
}


void ctrie_add(ctrie* map, char* word) {

}

void ctrie_remove(ctrie* map, char* word) {

}

//======= TESTING FUNCTIONS ================

ctrie* ctrie_create_test() {
	ctrie* map = ctrie_create();

	size_t i = 0;
	while (i < CTRIE_KEY_LENGTH)
		map->root->child[i++] = create_node();

	return map;
}

size_t ctrie_test_value(ctrie* map) {
	return sizeof(map->root->child);
}